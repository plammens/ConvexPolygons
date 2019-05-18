import glob
import re


pattern = re.compile(r"-D(?= *-D)")


for filename in glob.glob("CMakeFiles/*.dir/flags.make"):
    print("Inspecting '{}'. ".format(filename), end='')

    with open(filename, 'r') as file:
        lines = file.readlines()

    assert "CXX_DEFINES" in lines[6]
    found_problems: bool = bool(re.search(pattern, lines[6]))
    if found_problems:
        print("Editing... ", end='')
        lines[6] = re.sub(r"-D(?= *-D)", "", lines[6])
        
        with open(filename, 'w') as file:
            file.writelines(lines)
            
        print("Done.")
    else:
        print("No problems found.")

print("\nAll done. Try `make install` again.")