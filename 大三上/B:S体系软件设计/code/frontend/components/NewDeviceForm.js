import {
  Card,
  CardContent,
  CardHeader,
  Divider,
  Grid,
  TextField,
  Box,
  Button,
} from '@mui/material';
import React, { useState } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { setShow as higherSetShow } from '../redux/show.slice';
export default function NewDeviceForm(props) {
  // 需要发送
  //{
  //	type:'door',
  //	roomid:'132',
  //	description:'123',
  //	position:'12'
  //}
  const dispatch = useDispatch();
  const show = useSelector((state) => state.show.value);
  const setShow = (value) => {
    dispatch(higherSetShow(value));
  };
  let type = useSelector((state) => state.dragType.value);
  let roomid = useSelector((state) => state.room.value);
  let position = useSelector((state) => state.position.value);
  let houseid = useSelector((state) => state.houseID.value);
  let userid = useSelector((state) => state.userID.value);
  const [device, setDevice] = useState({
    name: '',
    description: '',
    ['type']: type,
    ['roomid']: roomid,
    ['position']: position,
    ['houseid']: houseid,
    ['userid']: userid,
  });

  const handleChange = (event) => {
    setDevice({
      ...device,
      // type: type,
      // roomid: roomid,
      // position: position,
      // houseid: houseid,
      // userid: userid,
      [event.target.name]: event.target.value,
    });
  };
  const handleClick = () => {
    setShow(false);
    console.log(device);
    setDevice({
      // ...device,
      type: type,
      roomid: roomid,
      position: position,
      houseid: houseid,
      userid: userid,
      name: '',
      description: '',
    });
  };
  return (
    <Box
      sx={{
        position: 'absolute',
        top: '15%',
        left: '30%',
        zIndex: show ? 9999 : -1,
      }}>
      <form noValidate>
        <Card>
          <CardHeader subheader='添加属于您的新设备' title='添加设备' />
          <Divider />
          <CardContent>
            <Grid container spacing={3}>
              <Grid item md={6} xs={12}>
                <TextField
                  fullWidth
                  helperText='请输入设备名'
                  label='device name'
                  name='name'
                  onChange={handleChange}
                  required
                  value={device.name}
                  variant='outlined'
                />
              </Grid>
              <Grid item md={6} xs={12}>
                <TextField
                  fullWidth
                  label='description'
                  name='description'
                  onChange={handleChange}
                  required
                  value={device.description}
                  variant='outlined'
                />
              </Grid>
            </Grid>
          </CardContent>
          <Divider />
          <Box
            sx={{
              display: 'flex',
              justifyContent: 'flex-end',
              p: 2,
            }}>
            <Button color='primary' variant='contained' onClick={handleClick}>
              确定添加
            </Button>
          </Box>
        </Card>
      </form>
    </Box>
  );
}
