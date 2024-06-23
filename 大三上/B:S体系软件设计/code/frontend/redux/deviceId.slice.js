import { createSlice } from '@reduxjs/toolkit';
const initialState = {
  value: -1,
};
const deviceId = createSlice({
  name: 'deviceId',
  initialState: initialState,
  reducers: {
    setDeviceId: (state, action) => {
      state.value = action.payload;
    },
  },
});
export const deviceIdReducer = deviceId.reducer;
export const { setDeviceId } = deviceId.actions;
