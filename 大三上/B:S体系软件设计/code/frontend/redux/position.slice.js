import { createSlice } from '@reduxjs/toolkit';
const initialState = {
  value: 0,
};
const positionSlice = createSlice({
  name: 'position',
  initialState: initialState,
  reducers: {
    setPosition: (state, action) => {
      state.value = action.payload;
    },
  },
});
export const positionReducer = positionSlice.reducer;
export const { setPosition } = positionSlice.actions;
