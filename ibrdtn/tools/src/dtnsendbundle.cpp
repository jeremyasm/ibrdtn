/*
* dtnsendbundle.cpp
*
* -- IBR-DTN example for Yaoxing --
*
* Copyright (C) 2015 IBR, TU Braunschweig
*
* Written-by: Björn Gernert <gernert@ibr.cs.tu-bs.de>
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
cout << "-- dtnsendbundle (IBR-DTN example for Yaoxing) --" << endl;
cout << "Syntax: dtnsend <dst>" << endl;
cout << " <dst> Set the destination eid (e.g. dtn://node/filetransfer)" << endl;
}
int main(int argc, char *argv[])
{
bool error = false;
string destination = "dtn://local/filetransfer";
string file_source = "";
ibrcommon::File unixdomain;
unsigned int lifetime = 3600;
if(argc <= 1 || argc > 2)
{
print_help();
return -1;
}
for (int i = 1; i < argc; ++i)
{
cout << argv[i] << endl;
if (argv[i][0] == '-')
{
std::string arg = argv[i];
// print help if requested
if (arg == "-h" || arg == "--help")
{
print_help();
return 0;
}
}
else
{
destination = argv[i];
}
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



// @Yaoxing: Add DBlock here
//remove const
dtn::data::DBlock &db = b.push_back<dtn::data::DBlock>();
db.setSrcDist(dtn::data::Integer(1));
db.setDestDist(dtn::data::Integer(2));
db.setType(dtn::data::Integer(1));
db.setDataName(BundleString("test on 1025!!!"));


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
