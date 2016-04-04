/*
* dtnsendbundle.cpp
*
* -- send a bundle with data name --
*
* Copyright (C) 2016 IBR, TU Braunschweig
*
* Modified-by: Yaoxing Li <liyaoxing1991@126.com>
* Inspired-by: Björn Gernert <gernert@ibr.cs.tu-bs.de>
*
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
#include "config.h"
#include <ibrdtn/api/Client.h>
#include <iostream>

#include "ibrdtn/data/DBlock.h"

void print_help()
{
	cout << "-- dtnsendbundle (send a bundle with data name) --" << endl;
	cout << "Syntax: dtnsend <dst> <dataName>" << endl;
	cout << " <dst> Set the destination eid (e.g. dtn://node/filetransfer)" << endl;
	cout << " <dataName> The name of the data to request (default value is DataName)" << endl;
}

int main(int argc, char *argv[])
{
 bool error = false;
 string destination = "dtn://local/filetransfer";
 string file_source = "";
 string dataNameTest = "";
 ibrcommon::File unixdomain;
 unsigned int lifetime = 3600;

 std::list<std::string> arglist;

 	for (int i = 0; i < argc; ++i)
 	{
 		if (argv[i][0] == '-')
 		{
 			std::string arg = argv[i];

 			// print help if requested
 			if (arg == "-h" || arg == "--help")
 			{
 				print_help();
 				return 0;
 			}
 			else
 			{
 				std::cout << "invalid argument " << arg << std::endl;
 				return -1;
 			}
 		}
 		else
 		{
 			arglist.push_back(argv[i]);
 		}
 	}

 	if (arglist.size() <= 1)
 	{
 		print_help();
 		return -1;
 	} else if (arglist.size() == 2)
 	{
 		std::list<std::string>::iterator iter = arglist.begin(); ++iter;

 		// the first parameter is the destination
 		destination = (*iter);
 		dataNameTest = "DataName"; //by default
 	}
 	else if (arglist.size() > 2)
 	{
 		std::list<std::string>::iterator iter = arglist.begin(); ++iter;

 		// the first parameter is the destination
 		destination = (*iter); ++iter;

 		// the second parameter is the dataName
 		dataNameTest = (*iter);
 	}

try {
// @Yaoxing: Now we try to connect to the IBR-DTN daemon
// Create a stream to the server using TCP.
ibrcommon::clientsocket *sock = NULL;
// check if the unixdomain socket exists
if (unixdomain.exists())
{
// connect to the unix domain socket
sock = new ibrcommon::filesocket(unixdomain);
}
else
{
ibrcommon::vaddress addr("localhost", 4550);
// connect to the standard local api port
sock = new ibrcommon::tcpsocket(addr);
}
ibrcommon::socketstream conn(sock);
try {
// Initiate a client for synchronous receiving
dtn::api::Client client(file_source, conn, dtn::api::Client::MODE_SENDONLY);
// Connect to the server. Actually, this function initiate the
// stream protocol by starting the thread and sending the contact header.
client.connect();
// target address
EID addr = EID(destination);
// @Yaoxing: Now we create a new bundle
cout << "Transfer bundle to " << addr.getString() << endl;

try {


dtn::data::Bundle b;

b.lifetime = lifetime;
b.destination = addr; // missed before, important



// @Yaoxing: Add DBlock here
dtn::data::DBlock &db = b.push_back<dtn::data::DBlock>();
db.setSrcDist(dtn::data::Integer(0));
db.setDestDist(dtn::data::Integer(2));
db.setType(dtn::data::Integer(0)); // 0: Interest, 1: Data
//db.setDataName(BundleString("DataName"));
db.setDataName(BundleString(dataNameTest));

client << b;
client.flush();
} catch (const ibrcommon::IOException &ex) {
std::cerr << "Error while sending bundle." << std::endl;
std::cerr << "\t" << ex.what() << std::endl;
error = true;
}
// Shutdown the client connection.
client.close();
} catch (const ibrcommon::IOException &ex) {
cout << "Error: " << ex.what() << endl;
error = true;
} catch (const dtn::api::ConnectionException&) {
// connection already closed, the daemon was faster
}
// close the tcpstream
conn.close();
} catch (const std::exception &ex) {
cout << "Error: " << ex.what() << endl;
error = true;
}
if (error) return -1;
return 0;
}
