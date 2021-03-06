#ifndef _LIBIPFWC_H
#define _LIBIPFWC_H
/* Library which manipulates firewall rules.  Version 0.1. */

/* This might not be the most efficient way of manipulating the rules,
 * but I'll maintain this as long as possible... */

/* (C)1998 Paul ``Rusty'' Russell - Placed under the GNU GPL (See
   COPYING for details). */

#include "ipfwc.h"

/* Gets the names of all the chains.  Returns internal pointer to
   array of ipfwc_fwchain.  Fills in num_chains.  You don't need to be
   root.  Returns NULL on error.*/
struct ipfwc_fwchain *ipfwc_get_chainnames(unsigned int *num_chains);

/* Take a snapshot of the rules; if zero is set, clears counters.
   Uses ipfwc_get_chainnames.  Returns internal pointer to array of
   ipfwc_fwrules.  Fills in num_rules.  You don't need to be
   root, unless zero is set.  Returns NULL on error. */
struct ipfwc_fwrule *ipfwc_get_rules(unsigned int *num_rules, int zero);

/* These functions return TRUE for OK or 0 and set errno.  If errno ==
   0, it means there was a version error (ie. upgrade libipfwc). */
/* Rule numbers start at 1 for the first rule. */

/* Insert the entry `fw' in chain `chain' into position `rulenum'. */
int ipfwc_insert_entry(const ip_chainlabel chain, 
                       const struct ip_fwuser *fw, 
                       unsigned int rulenum);

/* Atomically replace rule `rulenum' in `chain' with `fw'. */
int ipfwc_replace_entry(const ip_chainlabel chain, 
                        const struct ip_fwuser *fw, 
                        unsigned int rulenum);

/* Append entry `fw' to chain `chain'.  Equivalent to insert with
   rulenum = length of chain. */
int ipfwc_append_entry(const ip_chainlabel chain, const struct ip_fwuser *fw);

/* Delete the first rule in `chain' which matches `fw'. */
int ipfwc_delete_entry(const ip_chainlabel chain, const struct ip_fwuser *fw);

/* Delete the rule in position `rulenum' in `chain'. */
int ipfwc_delete_num_entry(const ip_chainlabel chain, unsigned int rulenum);

/* Check the packet `fw' on chain `chain'.  Returns the verdict, or
   NULL and sets errno. */
const char *ipfwc_check_packet(const ip_chainlabel chain, struct ip_fw *fw);

/* Flushes the entries in the given chain (ie. empties chain). */
int ipfwc_flush_entries(const ip_chainlabel chain);

/* Zeroes the counters in a chain. */
int ipfwc_zero_entries(const ip_chainlabel chain);

/* Creates a new chain. */
int ipfwc_create_chain(const ip_chainlabel chain);

/* Deletes a chain. */
int ipfwc_delete_chain(const ip_chainlabel chain);

/* Sets the policy on a built-in chain. */
int ipfwc_set_policy(const ip_chainlabel chain, const ip_chainlabel policy);

/* Translates errno numbers into more human-readable form than strerror. */
const char *ipfwc_strerror(int err);

/* These are the functions you should use from perl. */
/* ipfw_init is the main function and should be called via the others */

int ipfw_init(int args, char **arglist, unsigned int command, const char *chain, unsigned int rulenum);

int ipfw_append(int args, char **arglist, const char *chain);
int ipfw_delete(int args, char **arglist, const char *chain, unsigned int rulenum);
int ipfw_check(int args, char **arglist, const char *chain);
int ipfw_replace(int args, char **arglist, const char *chain, unsigned int rulenum);
int ipfw_insert(int args, char **arglist, const char *chain, unsigned int rulenum);
int ipfw_list(int args, char **arglist, const char *chain);
int ipfw_flush(int args, char **arglist, const char *chain);
int ipfw_zero(int args, char **arglist);
int ipfw_masq(int args, char **arglist);
int ipfw_new_chain(int args, char **arglist, const char *chain);
int ipfw_del_chain(int args, char **arglist, const char *chain);
int ipfw_set_policy(int args, char **arglist, const char *chain);

#endif /* _LIBIPFWC_H */
