#include "llc_auto_handler.h"
#include "llc_safe.h"
#include "llc_tcpip.h"

#ifndef LLC_ATMEL		

#if defined(LLC_WINDOWS)
#	include <WinSock2.h>
#else
	#include <sys/types.h>          /* See NOTES */
	#include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
#endif

#ifndef LLC_STDSOCKET_H_23627
#define LLC_STDSOCKET_H_23627

#if !defined(LLC_WINDOWS)
typedef int SOCKET;
#	ifndef INVALID_SOCKET
#		define INVALID_SOCKET -1
#	endif
#endif

namespace llc
{
	struct auto_socket_close : public ::llc::auto_handler<SOCKET, INVALID_SOCKET>					{
		using			TWrapper						::auto_handler;
		inline											~auto_socket_close					()	noexcept	{ close(); }
		inline			void							close								()	noexcept	{ llc_safe_closesocket(Handle); }
	};

	::llc::error_t			tcpipAddressToSockaddr		(uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint16_t port, sockaddr_in & sockaddr);
	::llc::error_t			tcpipAddressToSockaddr		(uint32_t address, uint16_t port, sockaddr_in & sockaddr);

	::llc::error_t			tcpipAddressFromSockaddr	(const sockaddr_in & sockaddr, uint8_t* a1, uint8_t* a2, uint8_t* a3, uint8_t* a4, uint16_t* port);
	::llc::error_t			tcpipAddressFromSockaddr	(const sockaddr_in & sockaddr, uint32_t & address, uint16_t & port);
	::llc::error_t			tcpipAddress				(SOCKET socket, uint8_t* a1, uint8_t* a2, uint8_t* a3, uint8_t* a4, uint16_t* port);

	stainli	::llc::error_t	tcpipAddressToSockaddr		(const ::llc::SIPv4End & addr, sockaddr_in & sockaddr)	{ return tcpipAddressToSockaddr		
		( ::llc::byte_at(addr.IP, 0)
		, ::llc::byte_at(addr.IP, 1)
		, ::llc::byte_at(addr.IP, 2)
		, ::llc::byte_at(addr.IP, 3)
		, addr.Port, sockaddr
		); 
	}
	stainli	::llc::error_t	tcpipAddressFromSockaddr	(const sockaddr_in& sockaddr, ::llc::SIPv4End & address)	{ uint8_t addr[4] = {}; llc_necs(tcpipAddressFromSockaddr	(sockaddr	, &addr[0], &addr[1], &addr[2], &addr[3], &address.Port)); address.IP = SIPv4{addr[0], addr[1], addr[2], addr[3]}; return 0; }
	stainli	::llc::error_t	tcpipAddress				(SOCKET socket, ::llc::SIPv4End & address)					{ uint8_t addr[4] = {}; llc_necs(tcpipAddress				(socket		, &addr[0], &addr[1], &addr[2], &addr[3], &address.Port)); address.IP = SIPv4{addr[0], addr[1], addr[2], addr[3]}; return 0; }
} // namespace


#endif // LLC_STDSOCKET_H_23627

#endif // LLC_ATMEL
