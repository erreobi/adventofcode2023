import sys
import re

ON="on"
OFF="off"
LOW="low"
HIGH="high"

print("FileName: ", sys.argv[1])

def leggi_file(nome_file):
    with open(nome_file, "r") as file:
        contenuto = file.read()
    return contenuto

class Module:

    def __init__(self, name, destination_modules, input_modules=[]) -> None:
        self.status=OFF
        self.destination_modules=destination_modules
        self.input_modules=input_modules
    def __init__(self, name="", destination_modules=None, input_modules=None, module_instance=None ) -> None:
        if module_instance is None:
            super().__init__(destination_modules, input_modules)
        else
            super().__init__(module_instance.name, module_instance.destination_modules, module_instance.input_modules)
        self.type=""


    def send(self, pulse):
        return [];

class Broadcaster(Module):
    def __init__(self, name="", destination_modules=None, input_modules=None, module_instance=None ) -> None:
        if module_instance is None:
            super().__init__(destination_modules, input_modules)
        else
            super().__init__(module_instance.name, module_instance.destination_modules, module_instance.input_modules)
        self.type=""

class FlipFlop(Module):
    def __init__(self, name="", destination_modules=None, input_modules=None, module_instance=None ) -> None:
        if module_instance is None:
            super().__init__(destination_modules, input_modules)
        else
            super().__init__(module_instance.name, module_instance.destination_modules, module_instance.input_modules)
        self.type="%"

class Conjunction(Module):
    def __init__(self, name="", destination_modules=None, input_modules=None, module_instance=None ) -> None:
        if module_instance is None:
            super().__init__(destination_modules, input_modules)
        else
            super().__init__(module_instance.name, module_instance.destination_modules, module_instance.input_modules)
        self.type="&"

def main():
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    module_configuration = leggi_file(nome_file)

    pulse_list = module_configuration.split("\n")
    print(pulse_list)
    for pulse_command in pulse_list:
        if (pulse_command is not ""):
            pulse_cmd = pulse_command.split(" -> ");
            sender=pulse_cmd[0]
            receivers=pulse_cmd[1].split(", ")
            print(f"Sender: {sender}")
            print(f"Receiver: {receivers}")




if __name__ == "__main__":
    main()
