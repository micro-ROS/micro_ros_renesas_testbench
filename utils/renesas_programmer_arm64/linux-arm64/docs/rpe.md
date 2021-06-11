# Overview
This document describes the encryption utility program that works on Linux and Windows.

An "rpe", which is bundled with this product, can be used to encrypt or decrypt program files.  

## Supported Operating Systems
* Linux (Ubuntu 18.04 LTS, x64/ARM32/ARM64)
* Linux (Ubuntu 20.04 LTS, x64/ARM32/ARM64)
* Windows 10 (32/64bit)

## Operating Environment
Please refer to the document for rfp-cli (`rfp-cli.md`).

## Command Line
The rpe command makes control from a command possible on Linux.

## Exit Code 
When the operation was successful, exit code 0 is returned.
Otherwise, 1 is returned.

## Command-line Syntax 
`rpe <file> -password <password> [options...]`

Option names are prefixed by a hyphen (-) or a slash (/).

## Options
The following lists start options for the encryption utility program.

|Option|Description|
|---|---|
|file|Specifies the file to be input (this specification is mandatory).<br>- The file can be specified as a relative path from the working directory.<br>- Files to be encrypted: Intel Hex, S-Record, HCUHEX, and RPI<br>- Files to be decrypted: RPE|
|password|Specifies the password for use in encrypting or decrypting the file (this specification is mandatory).<BR>If the password includes symbols, enclose each in double-quotation marks (").|
|decrypt|Decrypts an encrypted file (RPE).<BR>If this option is not specified, the file is encrypted.|
|output|Specifies the destination for output of a file.<BR>If this option is not specified, the directory holding the input files is used.<BR>- The file can be specified as a relative path from the working directory.|
|nooverwrite|Prohibits overwriting of output files.|
|?|Displays help information on the options.|

Caution:  
Pathnames that include spaces must be enclosed in double-quotation marks (").  

Remark:  
Enter a password made up of alphanumeric characters and symbols (up to 64 characters). The usable symbols are as follows.  
!, @, #, $, ^, &, *, (, ), _, -, +, =, [, ], {, }, ;, :, <, >, |, ., /, ?

Example:
```
rpe "out.hex" -password "0123456789"
rpe "out.hex" -password "0123456789" -output "out.rpe"
rpe "out.rpe" -decrypt -password "0123456789" -output "D:\outputdir\"
``` 