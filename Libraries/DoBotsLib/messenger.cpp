#include "messenger.h"

Messenger::Messenger(handleControl_func onControl_cb, handleCommand_func onDisconnect_cb,
		  handleCommand_func onSensorRequest_cb, handleDrive_func onDrive_cb, handleCustom_func onCustom_cb) :
	onControl(onControl_cb),
	onDisconnect(onDisconnect_cb),
	onSensorRequest(onSensorRequest_cb),
	onDrive(onDrive_cb),
	onCustom(onCustom_cb) {
}

boolean Messenger::handleMessages() {
	aJsonObject* item;
	int left = 0, right = 0;
	boolean enabled = false;
	
	item = readMessage();
	if (item == NULL) {
		return false;
	}

	switch(getType(item)) {
		case DRIVE_COMMAND:
			if (onDrive != NULL) {
				decodeDriveCommand(item, &left, &right);
				onDrive(left, right);
			}
			break;
		case CONTROL_COMMAND:
			if (onControl != NULL) {
				decodeControlCommand(item, &enabled);
				onControl(enabled);
			}
			break;
		case DISCONNECT:
			if (onDisconnect != NULL) {
				onDisconnect(item);
			}
			break;
		case SENSOR_REQUEST:
			if (onSensorRequest != NULL) {
				onSensorRequest(item);
			}
			break;
		default:
			if (onCustom != NULL) {
				onCustom(item);
			}
			break;
	}
	aJson.deleteItem(item);

	return true;
}
