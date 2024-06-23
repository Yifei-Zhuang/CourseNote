import { configureStore } from '@reduxjs/toolkit';
import { reducer } from './reducers';
import storage from 'redux-persist/lib/storage';
import { persistReducer, persistStore } from 'redux-persist';
import thunk from 'redux-thunk';
const persistConfig = {
  key: 'root',
  ['storage']: storage,
  whitelist: ['userID', 'houseID', 'room', 'userName', 'deviceId'],
};
const persistedReducer = persistReducer(persistConfig, reducer);

const store = configureStore({
  ['reducer']: persistedReducer,
  devTools: process.env.NODE_ENV !== 'production',
  middleware: [thunk],
});
let persistor = persistStore(store);
export { store, persistor };
