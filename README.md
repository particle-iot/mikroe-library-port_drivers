# Porting MikroE Click Libraries into Particle
This guide will walk you through the steps of porting MikroE Click libraries into Particle. The process involves adapting the library folder structure and library code to be compatible with Particle's firmware and hardware.
## Prerequisites
Before you begin, make sure you have the following:
- A Particle device (either M.2 or Feather Form Factor)
- A MikroE [Click Shield for Particle Gen 3](https://www.mikroe.com/click-shield-for-particle-gen-3) or [Feather Click Shield](https://www.mikroe.com/feather-click-shield) or another interface between Particle device and Click board
- A MikroE Click Board
- [Particle Workbench](https://www.particle.io/workbench/) installed
   > **Note:** This procedure can only be done using Particle Workbench and cannot be used using the Web IDE.
- A `mikroSDK 2.0.0.0` MikroE Click library that you want to port
- Download the Particle Driver Layer found in this repo
- A basic understanding of Particle's firmware and hardware

<br>

----
## Porting Procedure

### Download MikroE Click Example 
1. Navigate to the [MikroE Click Board](https://www.mikroe.com/click) site you want to port.
2. Under the Downloads section, click the example on Libstock.
3. Some older libraries use `mikroSDK 1.0.0.0` and in these, you will want to use the newer 2.0.0.0 version by selecting the `mikroSDK Library 2.0.0.0` tab. Download the zip folder and decompress/unpack.
   ![](/docs/tab.png)
   > **Note:**  Some libraries use the older mikroSDK Library 1.0.0.0 and these are not compatible. By default the Libstock page may default to this older version.
4. In the library directory, navigate to Examples/example and copy the source(`.c`) and header(`.h`) files. These files will need to be copied into the Particle Project.
   > **Note:**  Many libraries examples contain an example, and this example can be used a a reference for interfacing with the library. This is typically the `main.c` file.  

### Create Particle Project and Modify Folder Structure
1. Create a new Particle project. In the Particle Workbench, create a new project and give it a name that is related to the library you are porting.
2. Navigate to the folder where the project was created. You should see a folder  `/src`, a `project.properties` document and a `README.md`. Create a new folder named `lib` and this is where the MikroE library files and Particle Driver layer will be added in the following steps. The folder structure should follow `/lib/<example-library>/src` under `/<project dir>`.  
   > **Note:**  The folder naming and structure is specific, any deviation from this can result in issues with the MikroE library port.  
3. In the folder`/lib` , create a folder name for the MikroE library port (`example-library` is the example name shown).  
   > **Note:**  Do not include any spaces in the folder name as Workbench will not find the library files.  
4. Under the new library folder, create another folder named `src` and this is where you will want to move the MikroE library source and header files downloaded earlier.  
   ![](/docs/src.png)  
5. In the lib folder, move the downloaded Particle Driver layer into the `/lib` directory. The name of the root folder is `mikroe-port-drv`.  
   ![](/docs/drv.png)  
6. With Workbench open and the project open, you should now see the both the MikroE and the Particle Port Drivers in Workbench.    
   ![](/docs/vs-folder.png)      

<br>

----
## MikroE Click Library Modifications  
> **Note:**  Do not include any spaces in the folder name as Workbench will not find the library files.   

1. In Workbench, open the Mikroe Library header file(s). If the header file(s) contain the following, it should either be removed or commented out. Save the file(s).  
   ```
   #ifdef __cplusplus  
      extern "C"{  
   #endif
     ```  
   If the file(s) do contain, you will also need to remove/comment the following (typically found closer to the end of the file). 
   ```
   ifdef __cplusplus  
      }  
   #endif  
    ```  
2. In Workbench, navigate to the MikroE Library source file(s). Right click on each of the file(s) and change the file extension from .c to .cpp. Save the file(s).   
3. Open the editor commands in VS Code (CTRL+SHIFT+P using Windows or CMD+SHIFT+P using Mac) and select Particle: Clean Application (Local).   
   > **Note:** This will ensure the compiler sees the changes in the file extension and folder structure.  

<br>

----
## Particle Project
1. In the .ino file that was created, include the Mikro E Library Header file(s).  
   ```
   #include "example-library.h"
   ```  
2. Add the application specific code, leveraging the application example created by MikroE (`main.c`).  
3. Compile project. If there are any compile errors related to the ported library, modify the library to get rid of the errors. This may involve changing data types, rewriting function calls, or adding new code to handle specific tasks.  
4. Test the library code. Once you have modified the library code, test it on your Particle device to make sure it works as expected. You may need to make additional modifications based on your testing results.  

<br>

----
## Conclusion
Porting mikroE Click libraries into Particle requires some modifications to the Particle Project file structure, and may require some adaptation of the library code to work with Particle's firmware and hardware. By following these steps, you can successfully port a mikroE library into Particle.



















# mikroe_port

A Particle project named mikroe_port

## Welcome to your project!

Every new Particle project is composed of 3 important elements that you'll see have been created in your project directory for mikroe_port.

#### ```/src``` folder:  
This is the source folder that contains the firmware files for your project. It should *not* be renamed. 
Anything that is in this folder when you compile your project will be sent to our compile service and compiled into a firmware binary for the Particle device that you have targeted.

If your application contains multiple files, they should all be included in the `src` folder. If your firmware depends on Particle libraries, those dependencies are specified in the `project.properties` file referenced below.

#### ```.ino``` file:
This file is the firmware that will run as the primary application on your Particle device. It contains a `setup()` and `loop()` function, and can be written in Wiring or C/C++. For more information about using the Particle firmware API to create firmware for your Particle device, refer to the [Firmware Reference](https://docs.particle.io/reference/firmware/) section of the Particle documentation.

#### ```project.properties``` file:  
This is the file that specifies the name and version number of the libraries that your project depends on. Dependencies are added automatically to your `project.properties` file when you add a library to a project using the `particle library add` command in the CLI or add a library in the Desktop IDE.

## Adding additional files to your project

#### Projects with multiple sources
If you would like add additional files to your application, they should be added to the `/src` folder. All files in the `/src` folder will be sent to the Particle Cloud to produce a compiled binary.

#### Projects with external libraries
If your project includes a library that has not been registered in the Particle libraries system, you should create a new folder named `/lib/<libraryname>/src` under `/<project dir>` and add the `.h`, `.cpp` & `library.properties` files for your library there. Read the [Firmware Libraries guide](https://docs.particle.io/guide/tools-and-features/libraries/) for more details on how to develop libraries. Note that all contents of the `/lib` folder and subfolders will also be sent to the Cloud for compilation.

## Compiling your project

When you're ready to compile your project, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE. The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including your `.ino` application file
- The `project.properties` file for your project
- Any libraries stored under `lib/<libraryname>/src`
