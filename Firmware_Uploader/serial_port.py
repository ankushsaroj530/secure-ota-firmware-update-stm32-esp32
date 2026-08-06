import serial
import time
from config import *

ser = None


def connect():
    global ser

    ser = serial.Serial(
        port=COM_PORT,
        baudrate=BAUDRATE,
        bytesize=serial.EIGHTBITS,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        timeout=2,
        write_timeout=2
    )

    # Short delay for USB-UART stabilization
    time.sleep(0.1)

    print(f"[SERIAL] Connected to {COM_PORT}")


def write(data):
    global ser

    if isinstance(data, str):
        data = data.encode()

    ser.write(data)
    ser.flush()

    print(f"[TX] {len(data)} bytes")


def read(size):
    global ser
    return ser.read(size)


def read_line():
    global ser

    line = ser.readline()

    if line:
        try:
            print("[RX]", line.decode(errors="ignore").strip())
        except:
            print("[RX]", line)

    return line


def read_all():
    global ser

    time.sleep(0.1)

    data = ser.read_all()

    if data:
        try:
            print(data.decode(errors="ignore"))
        except:
            print(data)

    return data


def wait_for(text, timeout=10):
    """
    Wait until a specific string is received.
    Returns True if found, False on timeout.
    """

    start = time.time()

    while time.time() - start < timeout:

        line = read_line()

        if not line:
            continue

        if text.encode() in line:
            return True

    return False


def reset_input_buffer():
    global ser

    if ser and ser.is_open:
        ser.reset_input_buffer()


def reset_output_buffer():
    global ser

    if ser and ser.is_open:
        ser.reset_output_buffer()


def close():
    global ser

    if ser and ser.is_open:
        ser.close()
        print("[SERIAL] Port Closed")