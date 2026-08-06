import struct
import zlib
import hashlib
# Change this whenever you build a new firmware
FIRMWARE_VERSION = 147
# Unique device identifier
DEVICE_ID = 1
AUTH_TOKEN = b"STM32_OTA_2026!"


def create_header(firmware_data):

    firmware_size = len(firmware_data) 
    firmware_crc = zlib.crc32(firmware_data) & 0xFFFFFFFF

    firmware_sha256 = hashlib.sha256(firmware_data).digest()

    # Header Layout:
    # [Firmware Size]
    # [Firmware Version]
    # [Firmware CRC]
    # [Device ID]
    header = struct.pack(
    "<IIII16s32s",
    firmware_size,
    FIRMWARE_VERSION,
    firmware_crc,
    DEVICE_ID,
    AUTH_TOKEN,
    firmware_sha256
)


    print("\n========== Firmware Header ==========")
    print(f"Firmware Size    : {firmware_size} Bytes")
    print(f"Firmware Version : {FIRMWARE_VERSION}")
    print(f"Firmware CRC32   : 0x{firmware_crc:08X}")
    print(f"Device ID        : {DEVICE_ID}")
    print(f"Auth Token       : {AUTH_TOKEN.decode('ascii')}")
    print(f"SHA-256          : {firmware_sha256.hex()}")
    print("=====================================\n")

    return header