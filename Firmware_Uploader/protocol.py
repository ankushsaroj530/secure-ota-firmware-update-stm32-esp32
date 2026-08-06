CMD_UPDATE = b'U'
CMD_DATA = b'D'
CMD_END = b'E'

def get_version_command():
    return bytes([0x04])

def update_command():
    return CMD_UPDATE

def data_command():
    return CMD_DATA

CMD_EXIT = 0x05

def exit_command():
    return bytes([CMD_EXIT])

def end_command():
    return CMD_END