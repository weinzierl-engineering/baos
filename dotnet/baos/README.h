//
// Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#pragma once

namespace kdrive
{
namespace baos
{
namespace bindings
{

/*!

	\mainpage

	\section Introduction

	The kdrive BAOS client library is a C++ implementation
	of the KnxBAOS Protocol Version 1.2 and 2.0. This library implements
	a managed C++ .NET wrapper to enable application development with C# or
	Visual Basic .NET.

	The bindings are found in the kdriveBAOS_dotnet.dll DLL. To use this DLL
	in your project you need to add a reference. You can do this in a number of ways,
	one of which is to select the project in the solution browser, right click, and
	select Add Reference... Once you have added the DLL as a reference to your project
	you can view the API with the Object Browser. Unfortunately the document
	commenting system doesn't propagate from the C++ project, so the API
	in the Object Browser is without comments.

	\section API

	The API is currently a subset of the native C++ kdrive baos API.
	The C++ implementation includes all the protocol services in addition
	to the interpretation classes (i.e. the classes contained in this wrapper).
	For most applications you would not need such low level access
	(i.e. raw access to the protocol byte stream) however if there is a function
	(or functionality) missing from the API please contact us at Weinzierl Engineering
	and we'll do our best to incorporate your suggestions.	
*/

}
}
} // end namespace kdrive::baos::bindings

