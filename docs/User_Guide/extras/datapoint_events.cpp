
// connect to the baos events
BaosEvent baosEvent(connector);
baosEvent.setDatapointEvent(onDatapointEvent);
baosEvent.setBusConnectedEvent(onBusConnectedEvent);

