import { createSlice } from '@reduxjs/toolkit';
const initialState = {
  value: 0,
};
const roomSlice = createSlice({
  name: 'room',
  initialState: initialState,
  reducers: {
    setRoom: (state, action) => {
      state.value = action.payload;
    },
  },
});
export const roomReducer = roomSlice.reducer;
export const { setRoom } = roomSlice.actions;
