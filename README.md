# DotX64Dbg (EARLY ALPHA)
Plugins and Scripting with C# for x64Dbg.

# Create Plugins for X64Dbg with ease
DotX64Dbg aims to provide a seamless way to write and test plugins
for X64Dbg using .Net 5.0 and C#.

You can create/edit/debug plugins without ever restarting x64Dbg.
![Live Coding](.github/media/livecoding.gif?raw=true)

This gif showcases how you debug and edit your plugin at the same
time, this also showcases how you can register custom commands for
x64Dbg on the fly, the same works also for expressions.

## No more binaries
DotX64Dbg does not load the plugins as binaries instead it will
automatically compile your plugin code as soon something changes
and reloads it, this also means all plugins will be shipped as pure
code which means its a lot harder to hide malicious code in there.

# Installing
There is currently no official release. You can grab the latest artifacts
from the CI to try it out or build it yourself. Also older versions of
x64dbg are not supported by this plugin, we recommend to use the latest
builds.

# Your first Plugin
Creating new plugins is as easy as creating a new folder with two new files.
By default the DotX64Dbg plugins are located in the root directory of X64Dbg 
called ```dotplugins``` this can be however configured via ```dotx64dbg.json```.

Simply create a new folder in ```dotplugins``` called ```SamplePlugin```, plugins
are required to have a file called ```plugin.json``` which should look like
following:
```json
{
  "Name": "Sample Plugin",
  "Description": "My awesome plugin",
  "Version": "1.0.0",
  "Author": "Bob",
  "Website": "http://github.com/[youruser]/yourplugin",
  "Settings": {
    "Test": true
  }
}
```
Without the ```plugin.json``` file plugins will not load. The last thing
you need is some code that defines the plugin entry class, this is done by
deriving from ```IPlugin```, you can have only one class that derives from 
this interface. 
Create a file named ```SamplePlugin.cs```, you can choose any filename you like. 
To bootstrap the plugin you need at least following minimal example:
```csharp
using System;
using Dotx64Dbg;

public class SamplePlugin : IPlugin
{
    public SamplePlugin()
    {
        // Constructor, only called during first load
    }
    
    // Called as soon the plugin is fully initialized, this is called after
    // the constructor and only once the for the initial plugin load.
    public void Startup()
    {
        Console.WriteLine("Startup time!");
    }
    
    // Called before the plugin is about to be unloaded.
    public void Shutdown()
    {
        Console.WriteLine("We are about to go offline");
    }
}
```
After the two files are created DotX64Dbg will detect the changes
and immediately starts compiling/(re-)loading the plugin. DotX64Dbg
will also automatically generate a ```.csproj``` file with the correct
assembly references being setup. If you want to debug your plugins
simply attach Visual Studio to x64Dbg and place the breakpoints where
you would like to stop, its as simple as that.

There is also test plugin available [here](bin/dotplugins/myplugin)

# Scripting
DotX64Dbg also provides a scripting interface, unlike plugins a script
will be without state and only executes once. Scripts can use the same
APIs as plugins. To execute scripts use following command:
```
dotscript <path to script file>
```
You can find an example script [here](bin/dotscripts/TestScript.cs)

# Building

## Requirements
- Net 5.0 SDK.
- Visual Studio 2019 Community or greater.
- Vcpkg
- Zydis

## Vcpkg
Vcpkg is currently required with the integration setup. This is planned
to change in the future.

## Building
After everything is setup you should be open Dotx64Dbg.sln and be able
to build the entire solution.

# Documentation
The plan is to document all public API which also makes the documentation
available to Intellisense. A good starting point is to check the plugin
example, a lot of functions and classes already have minimal documentation, 
the best way to find out whats there is to explore the Assembly in Visual Studio 
with the Object Explorer.
![Object Explorer](.github/media/objectexplorer.png?raw=true)
