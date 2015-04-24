
ScopedBaosConnection connection("device_name");
Connector::Ptr connector = connection.getConnector();
BaosDatapoint d(connector, 1);	
d.setBoolean(enabled);

