//
// Copyright (c) 2002-2018 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#ifndef __KDRIVE_BAOS_CORE_FIX_POCO_EXCEPTION_H__
#define __KDRIVE_BAOS_CORE_FIX_POCO_EXCEPTION_H__

#include "kdrive/baos/Config.h"

/*!
	In earlier versions of poco we don't have th e
	POCO_DECLARE_EXCEPTION_CODE macro, so add it here
	This fixes a compile problem when using the ancient version
	of poco available on ubuntu with apt-get
*/
#ifndef POCO_DECLARE_EXCEPTION_CODE

#define POCO_DECLARE_EXCEPTION_CODE(API, CLS, BASE, CODE) \
	class API CLS: public BASE														\
	{																				\
	public:																			\
		CLS(int code = CODE);														\
		CLS(const std::string& msg, int code = CODE);								\
		CLS(const std::string& msg, const std::string& arg, int code = CODE);		\
		CLS(const std::string& msg, const Poco::Exception& exc, int code = CODE);	\
		CLS(const CLS& exc);														\
		~CLS() throw();																\
		CLS& operator = (const CLS& exc);											\
		const char* name() const throw();											\
		const char* className() const throw();										\
		Poco::Exception* clone() const;												\
		void rethrow() const;														\
	};

#endif // POCO_DECLARE_EXCEPTION_CODE

#endif // __KDRIVE_BAOS_CORE_FIX_POCO_EXCEPTION_H__
