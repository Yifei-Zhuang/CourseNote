import { createSlice } from '@reduxjs/toolkit';
const initialState = {
  value: -1,
};
const userIDSlice = createSlice({
  name: 'userid',
  initialState: initialState,
  reducers: {
    setUserID: (state, action) => {
      state.value = action.payload;
    },
  },
});
export const userIDReducer = userIDSlice.reducer;
export const { setUserID } = userIDSlice.actions;
