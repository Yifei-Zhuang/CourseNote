import { createSlice } from '@reduxjs/toolkit';
const initialState = {
  value: false,
};
const showSlice = createSlice({
  name: 'show',
  initialState: initialState,
  reducers: {
    setShow: (state, action) => {
      state.value = action.payload;
    },
  },
});
export const showReducer = showSlice.reducer;
export const { setShow } = showSlice.actions;
