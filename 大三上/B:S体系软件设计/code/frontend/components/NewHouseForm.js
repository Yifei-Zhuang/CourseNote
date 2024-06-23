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
export default function NewHouseForm(props) {
  // {
  //     houseid:'132',
  //     userid:'123',
  //     houseName:"",
  //     description:'',
  //     roomcount:0,// 后端生成
  // }
  const { open, setOpen } = props;
  const [name, setName] = useState('');
  const [description, setDescription] = useState('');
  let houseid = useSelector((state) => state.houseID.value);
  let userid = useSelector((state) => state.userID.value);

  const [form, setForm] = useState({
    ['houseid']: houseid,
    ['userid']: userid,
    ['name']: name,
    ['description']: description,
  });

  const handleChange = (event) => {
    setForm({
      ...form,
      // type: type,
      // roomid: roomid,
      // position: position,
      // houseid: houseid,
      // userid: userid,
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
      url: 'http://localhost:9000/house/add',
      method: 'POST',
      data: {
        userId: parseInt(userid),
        houseName: form.name,
        description: form.description,
      },
      withCredentials: true,
      headers: {
        Accept: 'application/json',
        'Content-Type': 'application/json',
      },
    }).then((res) => {
      console.log(res);
    });
    setOpen(false);
  };
  return (
    <Box component='div'>
      <Dialog open={open} onClose={handleClose}>
        <DialogTitle>场所信息</DialogTitle>
        <DialogContent>
          <Grid container spacing={3}>
            <Grid item md={6} xs={12}>
              <TextField
                fullWidth
                helperText='请输入场所名'
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
                helperText='请输入场所介绍'
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
