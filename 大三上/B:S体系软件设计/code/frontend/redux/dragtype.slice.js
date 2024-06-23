import { createSlice } from '@reduxjs/toolkit';
const initialState = {
  value: '',
};
const dragType = createSlice({
  name: 'dragtype',
  initialState: initialState,
  reducers: {
    setType: (state, action) => {
      state.value = action.payload;
    },
  },
});
export const dragTypeReducer = dragType.reducer;
export const { setType } = dragType.actions;
