import struct
import time

import serial_port
import protocol
import firmware
import header

# ==========================================
# Connect
# ==========================================

serial_port.connect()

# ==========================================
# Read Installed Version
# ==========================================

print("Reading Installed Firmware Version...")

serial_port.write(protocol.get_version_command())

version_msg = serial_port.read_line()

installed_version = 0

if version_msg.startswith(b"VERSION:"):
    installed_version = int(
        version_msg.decode().replace("VERSION:", "").strip()
    )

print(f"Installed Version : {installed_version}")

# ==========================================
# Load Firmware
# ==========================================

fw = firmware.load_firmware()

print("\nFirst 32 bytes of BIN")

for i in range(0, 32, 4):
    print(f"{i:04X}: {fw[i:i+4].hex()}")

# ==========================================
# Create Header
# ==========================================

hdr = header.create_header(fw)

print(f"Header Size : {len(hdr)} Bytes")

print("\n========== Version Comparison ==========")
print(f"Installed Version : {installed_version}")
print(f"Incoming Version  : {header.FIRMWARE_VERSION}")

if header.FIRMWARE_VERSION <= installed_version:

    print("\nFirmware already installed.")
    print("Jumping to application...")

    serial_port.write(protocol.exit_command())

    ack = serial_port.read_line()

    print("Bootloader :", ack.decode(errors="ignore").strip())

    serial_port.close()
    exit()

print("Result : Update Allowed")
print("========================================")

# ==========================================
# Send UPDATE Command
# ==========================================

print("\nSending UPDATE Command...")

serial_port.write(protocol.update_command())

ack = serial_port.read_line()

print("Application Response :", ack.decode(errors="ignore").strip())

if b"ACK" not in ack:
    print("Application rejected UPDATE command.")
    serial_port.close()
    exit()

print("STM32 restarting...")

serial_port.close()

# Give STM32 time to reset
time.sleep(1.5)

# ==========================================
# Reconnect
# ==========================================

serial_port.connect()

print("Waiting for Bootloader...\n")

start = time.time()

while True:

    line = serial_port.read_line()

    if line:

        text = line.decode(errors="ignore").strip()

        print("STM32 :", text)

        if "Waiting for Header" in text:
            break

    if time.time() - start > 8:
        print("Bootloader Timeout")
        serial_port.close()
        exit()

print("\nBootloader Ready")

time.sleep(0.1)

# ==========================================
# Send Header
# ==========================================

print("\nSending Header...")

serial_port.write(hdr)

ack = serial_port.read_line()

print("Header ACK :", ack.decode(errors="ignore").strip())

if b"ACK" not in ack:
    print("Header rejected.")
    serial_port.close()
    exit()

ack = serial_port.read_line()

print("Erase ACK :", ack.decode(errors="ignore").strip())

if b"ACK" not in ack:
    print("Flash erase failed.")
    serial_port.close()
    exit()

print("\nApplication Area Erased")

# ==========================================
# Send Firmware
# ==========================================

PACKET_SIZE = 256

offset = 0
packet = 0

print("\nSending Firmware...\n")

while offset < len(fw):

    data = fw[offset:offset + PACKET_SIZE]

    serial_port.write(protocol.data_command())

    serial_port.write(struct.pack("<H", len(data)))

    serial_port.write(data)

    ack = serial_port.read_line()

    print(f"Packet {packet:03d} : {ack.decode(errors='ignore').strip()}")

    if b"ACK" not in ack:
        print("Packet Failed")
        serial_port.close()
        exit()

    offset += len(data)
    packet += 1

print("\nFirmware Upload Complete")

# ==========================================
# END
# ==========================================

print("\nSending END Command...")

serial_port.write(protocol.end_command())

ack = serial_port.read_line()

print("END ACK :", ack.decode(errors="ignore").strip())

if b"ACK" in ack:

    print("\nFirmware Verified Successfully\n")

    while True:

        line = serial_port.read_line()

        if not line:
            continue

        text = line.decode(errors="ignore").strip()

        print(text)

        if "LOG: END" in text or "LOG:END" in text:
            break

else:

    print("Firmware Verification Failed")

serial_port.close()

print("\nUpdate Finished")