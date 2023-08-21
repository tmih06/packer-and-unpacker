# Static files packer and unpacker
this can be used to pack multiple files then unpack it when needed and run some command on execute
# How to use
- I'm using gcc compiler and run this on window 10
1.**Compile the `packer.cpp`:**
```shell
g++ packer.cpp -o packer
```
2.**Run `packer.exe`:**
```shell
packer.exe
```
3.**Enter the path of the folderr containing files u want to pack**
**Example:** [this folder](https://github.com/tmih06/packer-and-unpacker/tree/main/test/example)
```shell
Path: "C:\packer-and-unpacker\test\example""
```
4.**Now the packer.exe will generate the file shellcode.h which contain all the bytes code of each file in the selected folder, compile the `unpacker.cpp`:**


-For my example:
![](https://github.com/tmih06/packer-and-unpacker/blob/main/images/screenshot.png)
```shell
g++ unpacker.cpp -o unpack -static
```
**Note:** shellcode.h and unpacker.cpp must be in the same folder while compiling
5.**Now on the next run of unpacker.exe it will extract all the bytes code into each file then run the command has been specified (if have)**
You can edit it [here](https://github.com/tmih06/packer-and-unpacker/blob/main/unpacker.cpp#L26)

# How it work
![](https://github.com/tmih06/packer-and-unpacker/blob/main/images/how%20it%20work.png)
