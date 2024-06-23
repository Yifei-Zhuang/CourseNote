import {
  Card,
  CardContent,
  CardHeader,
  Divider,
  Grid,
  TextField,
  Box,
  Button,
  DialogActions,
  Dialog,
  DialogTitle,
  DialogContent,
} from '@mui/material';
import React, { useState } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import axios from 'axios';
export default function AnotherNewDeviceForm(props) {
  // 需要发送
  //{
  //	type:'door',
  //    name:'133'
  //	roomid:'132',
  //	description:'123',
  //	position:'12'
  //}
  let type = useSelector((state) => state.dragType.value);

  let roomid = useSelector((state) => state.room.value);
  let houseid = useSelector((state) => state.houseID.value);
  let position = useSelector((state) => state.position.value);
  const { open, setOpen } = props;
  const [name, setName] = useState('');
  const [description, setDescription] = useState('');

  const [form, setForm] = useState({
    ['type']: type,
    ['position']: position,
    ['roomid']: roomid,
    ['name']: name,
    ['description']: description,
  });

  const handleChange = (event) => {
    setForm({
      ...form,
      [event.target.name]: event.target.value,
    });
  };
  const handleClose = () => {
    console.log(form);
    setOpen(false);
  };
  const handleSubmit = () => {
    console.log('form', form);
    // TODO 添加场所逻辑
    axios({
      url: 'http://localhost:9000/device/add',
      method: 'POST',
      data: {
        ['type']: type,
        ['position']: position,
        ['roomid']: roomid,
        ['deviceName']: form.name,
        ['description']: form.description,
        ['houseid']: form.houseid,
      },
      withCredentials: true,
      headers: {
        Accept: 'application/json',
        'Content-Type': 'application/json',
      },
    }).then((res) => {
      console.log(res);
      setName('');
      setDescription('');
    });
    setOpen(false);
  };
  return (
    <Box component='div'>
      <Dialog open={open} onClose={handleClose}>
        <DialogTitle>设备信息</DialogTitle>
        <DialogContent>
          <Grid container spacing={3}>
            <Grid item md={6} xs={12}>
              <TextField
                fullWidth
                helperText='请输入设备名'
                label='name'
                name='name'
                onChange={handleChange}
                required
                value={form.name}
                variant='outlined'
              />
            </Grid>
            <Grid item md={6} xs={12}>
              <TextField
                fullWidth
                helperText='请输入设备介绍'
                label='description'
                name='description'
                onChange={handleChange}
                required
                value={form.description}
                variant='outlined'
              />
            </Grid>
          </Grid>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleSubmit}>提交</Button>
          <Button onClick={handleClose}>取消</Button>
        </DialogActions>
      </Dialog>
    </Box>
  );
}
