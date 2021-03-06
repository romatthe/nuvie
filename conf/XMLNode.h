/*
Copyright (C) 2002 The Pentagram team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef XMLNODE_H
#define XMLNODE_H

#include <string>
#include <vector>


class	XMLNode
{
protected:
	std::string				id;
	std::string				content;
	std::vector<XMLNode*>	nodelist;
	bool					no_close;

public:
	XMLNode() : no_close(false)
		{  }
	XMLNode(const std::string &i) : id(i), no_close(false)
		{  }
	XMLNode(const XMLNode &n)
		: id(n.id),content(n.content),nodelist(n.nodelist), no_close(false)
		{  }
	~XMLNode();

	XMLNode &operator=(const XMLNode &n) {
		id=n.id; content=n.content; nodelist=n.nodelist; no_close = n.no_close;
		return *this;
	}

	const std::string &reference(const std::string &,bool &);
	const XMLNode *subtree(const std::string &) const;

	const std::string &value(void) const {
		return content;
	}

	typedef std::pair<std::string, std::string> KeyType;
	typedef std::vector<KeyType> KeyTypeList;

	bool searchpairs(KeyTypeList &ktl, const std::string &basekey,
					 const std::string currkey, const unsigned int pos);
	void selectpairs(KeyTypeList &ktl, const std::string currkey);

	std::string dump(int depth = 0);

	void xmlassign(const std::string &key, const std::string &value);
	void xmlparse(const std::string &s,std::size_t &pos);

	void listkeys(const std::string &,std::vector<std::string> &,
				  bool longformat=true) const;
};




#endif
