import { createSlice } from '@reduxjs/toolkit';
const initialState = {
  value: false,
};
const userNameSlice = createSlice({
  name: 'username',
  initialState: initialState,
  reducers: {
    setUserName: (state, action) => {
      state.value = action.payload;
    },
  },
});
export const userNameReducer = userNameSlice.reducer;
export const { setUserName } = userNameSlice.actions;
