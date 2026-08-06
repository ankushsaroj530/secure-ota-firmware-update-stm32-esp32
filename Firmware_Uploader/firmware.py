FIRMWARE_PATH = r"C:\Users\Ankush_Saroj\STM32CubeIDE\workspace_1.19.0\Secure_OTA_Firmware_System\STM32_Application\Debug\STM32_Application.bin"

def load_firmware():
    with open(FIRMWARE_PATH, "rb") as f:
        data = f.read()

    print("Firmware Loaded")
    print("Size:", len(data), "bytes")

    return data