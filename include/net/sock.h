/**
 * \file sock.h
 * \date Mar 17, 2009
 * \author anton
 * \brief Definitions for the AF_INET socket handler.
 */

#ifndef SOCK_H_
#define SOCK_H_

#include "net/net_device.h"
#include "net/net_packet.h"

/**
 * struct sock_common - minimal network layer representation of sockets
 */
struct sock_common {
        unsigned short          skc_family;
        volatile unsigned char  skc_state;
        unsigned char           skc_reuse;
        int                     skc_bound_dev_if;
/*        struct hlist_node       skc_node;
        struct hlist_node       skc_bind_node;
        atomic_t                skc_refcnt;
        unsigned int            skc_hash;
        struct proto            *skc_prot;
*/
};

/**
 * struct sock - network layer representation of sockets
 */
struct sock {
	struct sock_common      __sk_common;
	unsigned char		sk_protocol;
	unsigned short		sk_type;
	int			sk_rcvbuf;
	int			sk_sndbuf;
	unsigned long 		sk_flags;
	//TODO: implement queue
	struct socket           *sk_socket;
	net_device		*netdev;

	void (* sk_state_change) (struct sock *sk);
	void (* sk_data_ready) (struct sock *sk, int bytes);
	void (* sk_write_space) (struct sock *sk);
	void (* sk_error_report) (struct sock *sk);
	int (* sk_backlog_rcv) (struct sock *sk, net_packet*pack);
	void (* sk_destruct) (struct sock *sk);
};

#endif /* SOCK_H_ */
