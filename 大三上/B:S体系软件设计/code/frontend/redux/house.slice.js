import { createSlice } from '@reduxjs/toolkit';
const initialState = {
  value: -2,
};
const houseIDSlice = createSlice({
  name: 'houseID',
  initialState: initialState,
  reducers: {
    setHouseID: (state, action) => {
      state.value = action.payload;
    },
  },
});
export const houseIDReducer = houseIDSlice.reducer;
export const { setHouseID } = houseIDSlice.actions;
