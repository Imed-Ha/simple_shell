import os

# Global dictionary to store aliases
aliases = {}

# Function to print all aliases
def print_aliases():
    for alias, value in aliases.items():
        print(f"{alias}='{value}'")

# Function to print specific aliases
def print_alias(alias_names):
    for alias_name in alias_names:
        if alias_name in aliases:
            print(f"{alias_name}='{aliases[alias_name]}'")

# Function to set aliases
def set_alias(alias_name, alias_value):
    aliases[alias_name] = alias_value

last_exit_code = 0
# Function to parse user input
def parse_input(command):
    # Strip any leading or trailing whitespace from the command
    command = command.strip()
    # Check if the command is a comment (starts with '#')
    if command.startswith('#'):
        return
    # Execute the command if it is not a comment
    execute_command(command)
            
    if command.startswith("alias"):
        parts = command.split()
        if len(parts) == 1:
            print_aliases()
        elif len(parts) == 2:
            print_alias(parts[1:])
        else:
            for alias_definition in parts[1:]:
                alias_parts = alias_definition.split("=")
                alias_name = alias_parts[0]
                alias_value = alias_parts[1]
                set_alias(alias_name, alias_value)
    elif command.startswith("exit"):
        exit()
    else:
        os.system(command)
    # Add the following code before executing the command
    command = replace_variables(command)
    execute_command(command)
            
def replace_variables(command):
    # Replace $$ with process ID
    command = command.replace('$$', str(os.getpid()))

    # Replace $? with last exit code
    command = command.replace('$?', str(last_exit_code))

    return command


# Main shell loop
while True:
    user_input = input("$ ")
    parse_input(user_input)
