# Overview
This document describes the Renesas Flash Programmer utility program that works on Linux and Windows.

An "rfp-util", which is bundled with this product, can be used to run the following processing.   
* Encryption with the use of user factory programming keys (UFPKs) as DLM keys and user keys
* Generation of random UFPKs and initialization vectors (IVs)
* Output of UFPK files for the Renesas Key Wrapping Service
* Generation of Renesas key files
* Generation of RMA authentication codes with unique IDs

## Supported Operating Systems
* Linux (Ubuntu 18.04 LTS, x64/ARM32/ARM64)
* Linux (Ubuntu 20.04 LTS, x64/ARM32/ARM64)
* Windows 10 (32/64bit)

## Operating Environment
Please refer to the document for rfp-cli (`rfp-cli.md`).

## Command Line
The rpe-util command makes control from a command line possible under Linux.

## Exit Code 
When the operation was successful, exit code 0 is returned.
Otherwise, 1 is returned.

## Command-line Syntax 
`rfp-util [command] [options...]`

The following table gives descriptions of each item.

|Item|Description|
|---|---|
|rfp-util|A name of a file to be executed.|
|command|Command names prefixed by a slash (/) or a hyphen (-).<br>command: genufpk, genkey, or calcresponse|
|options...|Option names prefixed by a slash (/) or a hyphen (-).<br>- Specify parameters as required.<br>- Options and parameters are not case sensitive.<br>- Absolute or relative paths can be used for the name of the file.|
|?|Displays help information on the options.|

Caution:  
Pathnames that include spaces must be enclosed in double-quotation marks (").  

## List of Commands
The following table gives descriptions of each command.

|Command|Description|
|---|---|
|genufpk|Generates a UFPK file.<br>When generation was successful, the generated UFPK is displayed in the console.|
|genkey|Generates a Renesas key file.<br>When generation was successful, a wrapped UFPK (W-UFPK), IV, and encrypted key (including a message authentication code, MAC) are displayed in the console.|
|calcresponse|Calculates a response value for use in challenge-and-response authentication and outputs it to the console.|

## Options
The following lists start options for the key encryption utility program.

Remark:  
A hexadecimal data or binary file can be specified for the parameters indicated as Hex data. To
specify a file, use the path to the file with “file=” as a prefix.

### Common Options
|Option|Parameter|Description|
|---|---|---|
|output|File path|Specifies the name of a file to be output.<br>If this option is omitted, the execution result is output to the console.|
|nooverwrite|None|If an output file already exists, an error will occur.|

### genufpk Command Option
|Option|Parameter|Description|
|---|---|---|
|ufpk|Hex data|Specifies the output of 32 bytes of binary data.<br>If this option is omitted, a random value is used for ufpk.|

### genkey Command Options
|Option|Parameter|Description|
|---|---|---|
|iv|Hex data|Specifies an IV for use in encryption. The data size is 16 bytes.<br>If this option is omitted, a random value is used for IV.|
|ufpk|File path|Specifies a UFPK file used in encryption.|
|wufpk|File path|Specifies a W-UFPK file obtained from the Renesas Key Wrapping Service.|
|key|Hex data|- When the userkey option is not specified<br>&nbsp;&nbsp;&nbsp;Specifies the DLM key data. The data size is 16 bytes.<br>- When the userkey option is specified<br>&nbsp;&nbsp;&nbsp;Specifies the user key data.<br>&nbsp;&nbsp;&nbsp;For the key data format and data size, refer to the boot firmware manual.<br>Note that this tool does not check the user key size.|
|userkey|XX|Generates a user key. Specify the type of user key as a one-byte hexadecimal parameter. For the values to be entered, refer to the boot firmware manual.|

### calcresponse Command Options
|Option|Parameter|Description|
|---|---|---|
|challenge|Hex data|Specifies a challenge value (the unique ID of the device is usually specified).<br>The data size is 16 bytes.|
|key|Hex data|Specifies the DLM key data. The data size is 16 bytes.|

Example:
```
(genufpk)
rfp-util -genufpk -output "D:\example\ufpk.key"

(genkey)
rpe-util -genkey -ufpk file="D:\example\ufpk.key" -wufpk file="D:\example\ufpk_enc.key" -key "000102030405060708090A0B0C0D0E0F" -output "D:\example\abc.rkey"

(calcresponse)
rpe-util -calcresponse -challenge "ABCDEFGHIJKLMNOPQRSTUVWXYZ012345" -key "000102030405060708090A0B0C0D0E0F"
``` 