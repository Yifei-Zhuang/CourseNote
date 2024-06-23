import { dragTypeReducer } from './dragtype.slice';
import { houseIDReducer } from './house.slice';
import { positionReducer } from './position.slice';
import { roomReducer } from './room.slice';
import { showReducer } from './show.slice';
import { userIDReducer } from './userid.slice';
import { userNameReducer } from './username.slice';
import { combineReducers } from 'redux';
import { deviceIdReducer } from './deviceId.slice';
export const reducer = combineReducers({
  houseID: houseIDReducer,
  dragType: dragTypeReducer,
  position: positionReducer,
  room: roomReducer,
  show: showReducer,
  userID: userIDReducer,
  userName: userNameReducer,
  deviceId: deviceIdReducer,
});
