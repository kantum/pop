## SD Card Library
**Files**: `SD.h`, `SD.c`  
**Requires**: `SPI Library`  
**Uses**: None  
**Author**: Nil Burción `nburcion@student.42.fr`  
***

### Public
#### SD Initialization
> **Warning**: The Slave Select for the SD Card is made when `SD_init` is called. Two notes on that:
> 
> * Be sure to re-select the SD if deselected for some reason and you want to use it.
> * Be sure that the selection of the SD Card in `SD_init` doesn't interfere with your code

 

> **Warning**: The function `SD_init` must be the first function called. If not the behaviour for all the other functions is undefined. The only exception to this rule is `SD_initialized`  

| Prototype     	| `bool SD_init(void)`        |
|---------------	|:-----------------------------|
| _Explanation_	| Initializes the SD Card for use |
| _Details_		| <li> Lowers the Slave Select line for the SD card via `SPI_slave_select`</li><li>Puts the SD Card in SPI Mode.</li><li>Sends & Checks `CMD0` _(It retries the sending multiple times if it fails)_</li><li>Sends & Checks `CMD8`</li><li>Sends & Checks `CMD55+ACMD41` _(It retries the sending multiple times if it fails)_</li><li>Sends & Checks `CMD58`</li><li>Sends & Checks `CMD59`</li><li>Congrats the SD Card is initialized</li> Returns **`true`** or **`false`** depending on whether the initialization succeded or failed|


| Prototype     	| `bool SD_initialized(void)`        |
|---------------	|:-----------------------------|
| _Explanation_	| Returns **`true`** if the SD Card has been initialized successfully via `SD_init`, returns **`false`** otherwise |

-
#### SD Usage
> **Note**: The SD library always keeps a sector on the cache so contiguous reads of the same sector will benefit from a **huge** speed increase


| Prototype     	| `bool SD_read_byte(unsigned int sector, unsigned int relative_address, byte *b)`        |
|---------------	|:-----------------------------|
| _Explanation_	| Reads a single byte from a sector and a offset from that sector and stores the byte in `*b`. Returns **`true`** if the read was successful or **`false`** if it fails. |
| _Arg:_ **sector** | The sector _number_ intended to read |
| _Arg:_ **relative_address** | The relative address or offset starting from the sector's initial address. `relative_address` has to be inside the sector, or in other words, has to be <**`512`** |
| _Arg:_ **\*b** | The pointer to the variable where the byte will be written

> **Note**: Before returning **`false`** the function tries internally to re-read the byte up to 5 times. So usually re-running this function won't make sense.

Imagine we execute this code:

```c
byte b;
SD_read_byte(0x5, 0x42, &b);
```
The **real** address we are reading, is calculated via: Real Address = (`sector` * **`512`**) + `relative_address`;

The address of course is zero-based. (i.e. starts at index **`0`**)  
So in this example we would be reading the address **`0xA42`**


| Prototype     	| `bool SD_read_bytes(unsigned int sector, unsigned int start_rel_address, unsigned long bytes, void *b)`        |
|---------------	|:-----------------------------|
| _Explanation_	| Reads multiple bytes (currently only `1`, `2`, `4` and `8` supported) from a sector and a offset from that sector and stores the bytes in `*b`. Returns **`true`** if the read was successful or **`false`** if it fails. |
| _Arg:_ **sector** | The sector _number_ intended to read |
| _Arg:_ **start_rel_address** | The relative address or offset starting from the sector's initial address |
| _Arg:_ **bytes** | The number of bytes to read. Currently only `1`, `2`, `4` and `8` supported |
| _Arg:_ **\*b** | The pointer to the variable where the byte will be written

> **Warning**: This functon only supports reading from one sector so the bytes to read cannot cross the boundaries of a sector.  More specifically it means:  
> <center> (`start_rel_address` + `bytes` - **`1`**) < **`512`** </center>
> (If the expression above is not respected the function will return always **`false`**)


| Prototype     	| `bool SD_read_block(unsigned int sector, byte *b)`        |
|---------------	|:-----------------------------|
| _Explanation_	| Reads a whole block (sector) into a string (`*b`). Returns **`true`** on success **`false`** otherwise. |
| _Arg:_ **sector** | The sector _number_ intended to read |
| _Arg:_ **\*b** | The pointer to the variable where the bytes will be written. It seems stupid to note but take care `*b` is suited to fit 512 bytes!

***
### Private


| Prototype     	| `void SD_send_command(byte command, byte arg1, byte arg2, byte arg3, byte arg4, byte CRC`) |
|---------------	|:-----------------------------|
| _Explanation_	| Sends a command to the SD Card. It uses `SPI_queue_byte` and `SPI_send` (With all the consequences bla, bla, bla...)
| _Arg:_ **command** | The command to send to the SD Card. Use the macros defined in `SD.h`. So valid commands would be for example: `CMD0`, `CMD59`, `ACMD42`...
| _Arg:_ **arg1** | The first eight bits of the argument
| _Arg:_ **arg2** | The second eight bits of the argument
| _Arg:_ **arg3** | The third eight bits of the argument
| _Arg:_ **arg4** | The fourth eight bits of the argument
| _Arg:_ **CRC**  | The Cyclic Redundancy Check byte. Usually it's not checked so you can use **`0x00`** if you are not sure.


| Prototype     	| `bool SD_read_sector(unsigned int sector)` |
|---------------	|:-----------------------------|
| _Explanation_	| Loads a sector (block) of `512 Bytes` to the cache returns **`true`** on success or **`false`** otherwise.

> **Note**: This is explicitly internal so unless you're developing an ultra-fancy-shiny new feature for the SD Card Library, don't use it.

