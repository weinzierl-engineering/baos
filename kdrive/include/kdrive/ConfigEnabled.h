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

#ifndef __KDRIVE_CONFIG_ENABLED_H__
#define __KDRIVE_CONFIG_ENABLED_H__

/*************************************
** Configures optional kdrive components
**************************************/

/*!
	kdrive access USB Port
*/
#define KDRIVE_ACCESS_USB_ENABLED (1)

/*!
	kdrive access Tunnelling and Routing Port
*/
#define KDRIVE_ACCESS_IP_ENABLED (1)

/*!
	kdrive access FT1.2, Tiny Serial and Raw Serial Ports
*/
#define KDRIVE_ACCESS_SERIAL_ENABLED (1)

/*!
	kdrive access Baos Port
	BaosPort is an access port implementation
	of the BAOS binary protocol.
*/
#define KDRIVE_ACCESS_BAOS_ENABLED (1)

/*!
	kdrive access Datagram Port
	DatagramPort is an access port implementation
	of a raw UDP socket
*/
#define KDRIVE_ACCESS_DATAGRAM_ENABLED (1)

/*!
	kdrive access Link Layer Server Port
	LinkLayerServerPort is an access port implementation
	of the linux tiny serial server protocol
*/
#define KDRIVE_ACCESS_LLS_ENABLED (1)

/*!
*/
#define KDRIVE_ACCESS_LOOPBACK_ENABLED (1)

#endif // __KDRIVE_CONFIG_ENABLED_H__
