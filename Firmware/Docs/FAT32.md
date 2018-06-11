## FAT32 File System Library
**Files**: `FAT32.h`, `FAT32.c`
**Requires**: `SD Card Library` (and by extension `SPI Library`)
**Uses**: None
**Author**: Nil Burción `nburcion@student.42.fr`  
***

### Public
#### FAT32 Mounting

> **Warning**: As this library is mounted on top of the SD Card Library, which is mounted on top of the SPI Library all the warnings from those libraries apply to this one. Have that in account

 

> **Warning**: The function `FAT32_mount` must be the first function called. If not the behaviour for all the other functions is undefined. The only exception to this rule is `FAT32_mounted`  

| Prototype     	| `bool FAT32_mount(void)`     |
|---------------	|:-----------------------------|
| _Explanation_	| Mounts the FAT32 file system leaving it ready for the rest of functions. Returns **`true`** if the file system could be mounted successfully or **`false`** in case it failed.


| Prototype     	| `bool FAT32_mounted(void)`     |
|---------------	|:-----------------------------|
| _Explanation_	| Returns **`true`** if the file system was mounted successfully with `FAT32_mount` or **`false`** otherwise

#### File Operations

> **Notice**: This FAT32 implementation is very basic. Here are the most important limitations:
> 
> * It only supports FAT32. (It doesn't support FAT16 or others)
> * Currently there's no way to open directories so only files in the root folder are allowed.
> * It doesn't support long file names, so it means:
> 	* The file extension is limited to 3 characters
> 	* Only `A-Z`, `a-z`, `0-9` are allowed as filename characters.
> 	* The filename is limited to 11 characters (8 for the name + 3 for the extension)

> Also it should be noted that all files opened with this library will contain an internal pointer marking the position inside the file.
> 
> Another thing to know is that one should **NEVER** change any file attributte in any other way that's not via the file functions in this library.

| Prototype     	| `bool FAT32_fopen(file_t directory_cluster, char *filename, file_t *file)`     |
|---------------	|:-----------------------------|
| _Explanation_	| Tries to open a file on a given directory. If the file is found returns **`true`** and `*file` can be used as a valid file variable. If the file is not found or cannot be opened returns **`false`**.
| _Arg:_ **directory_cluster** | The folder where the file is contained. Use **`FAT32_ROOT_DIRECTORY`** for root folder
| _Arg:_ **\*filename** | A null terminated string that contains the file name (extension included) |
| _Arg:_ **\*file** | A pointer to an empty `file_t` variable. If the function returns **`true`** this variable will be ready to use as a file |


| Prototype     	| `bool FAT32_fgetc(file_t *file, char *c)`     |
|---------------	|:-----------------------------|
| _Explanation_	| Gets the next character from the file `*file`, writes it to `*c` and advances the file internal pointer. If no character could be readed (end of the file or fatal SD Card error) the function returns **`false`** if the character was read, the function returns **`true`**.
| _Arg:_ **\*file** | The file to access
| _Arg:_ **\*c** | Where to write the character


| Prototype     	| `unsigned int FAT32_fsize(file_t *file)`     |
|---------------	|:-----------------------------|
| _Explanation_	| Returns, given a valid file, it's size
| _Arg:_ **\*file** | The file you want to know the size of

| Prototype     	| `bool FAT32_fseek(file_t *file, unsigned int position)`     |
|---------------	|:-----------------------------|
| _Explanation_	| Move the file pointer to a certian position. Returns **`true`** on success or **`false`** if the position couldn't be seeked. If the file fails to seek the position the previous position on the fail remains.
| _Arg:_ **\*file** | The file whose pointer position you want to change
| _Arg:_ **position** | The new position of the file


| Prototype     	| `unsigned int FAT32_fpos(file_t *file)`     |
|---------------	|:-----------------------------|
| _Explanation_	| Returns, given a valid file, it's cursor's position
| _Arg:_ **\*file** | The file whose pointer position you want to know

***
### Private

| Prototype     	| `unsigned int FAT32_filename_matches(file_t directory_cluster, char *filename)`     |
|---------------	|:-----------------------------|
| _Explanation_	| Internal function used by `FAT32_fopen`. **Do not use**

| Prototype     	| `void FAT32_setup_file(file_t directory, file_t *file)`     |
|---------------	|:-----------------------------|
| _Explanation_	| Internal function used by `FAT32_fopen`. **Do not use**



