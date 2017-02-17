
Build the SDK as decribed in README.adoc or in User_Guide.adoc

Make sure that the WZSDK_BINDINGS option is set to one

After successful building the `kdriveBAOS_dotnetd.dll` and `kdriveBAOS_dotnet.dll` files can be found inside the `/build/bin/Debug` or `/build/bin/Release` folders

Copy the kdriveBAOS_dotnet.dll and optional the kdriveBAOS_dotnet.xml (for intellisense) into the bin/{Platform e.g. Visual Studio 12 2013} directory from 
cmake build directory kdrive/bin/Release

kdrive_baos_samples_csharp_vs120.sln
	Solution file for Visual Studio 12 2013
	.NET Framework 4.5
	Platform Target x86
	
If you use another .NET version or for other platform (e.g. 64bit) you'll have to change the C# project properties.

To create the intellisense file kdriveBAOS_dotnet.xml you need to enable the xml documenation generation.
See http://msdn.microsoft.com/en-us/library/ms173501%28v=vs.90%29.aspx
