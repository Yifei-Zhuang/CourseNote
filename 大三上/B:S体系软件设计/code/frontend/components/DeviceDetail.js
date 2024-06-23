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
  Typography,
} from '@mui/material';
import React, { useState, useEffect } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import axios from 'axios';
import styled from '@emotion/styled';
import { setDeviceId } from '../redux/deviceId.slice';
const MyTextField = styled(TextField)(({ theme }) => ({
  WebkitTextFillColor: 'black',
}));
export default function DeviceDetail(props) {
  const deviceid = useSelector((state) => state.deviceId.value);
  const { deviceDetailOpen, setDeviceDetailOpen } = props;
  //所要做的就是获取当前的状态
  const [loading, setLoading] = useState(true);
  const [deviceInfo, setDeviceInfo] = useState({});
  const [open, setOpen] = useState(false);
  const [value, setValue] = useState('');
  useEffect(() => {
    setLoading(true);
    axios({
      url: 'http://localhost:9000/device/getSingle',
      method: 'GET',
      params: {
        ['deviceid']: deviceid,
      },
      withCredentials: true,
      headers: {
        Accept: 'application/json',
        'Content-Type': 'application/json',
      },
    })
      .then((res) => {
        console.log(res);
        setDeviceInfo(res.data.result);
        console.log('deviceinfo', deviceInfo);
      })
      .catch((err) => {
        console.log(err);
      });
  }, [deviceid, deviceDetailOpen]);
  useEffect(() => {
    setLoading(false);
  }, [deviceInfo]);
  const handleClose = () => {
    setDeviceDetailOpen(false);
    setDeviceInfo({});
    setLoading(true);
    setOpen(false);
  };
  const handleStatus = () => {
    //TODO 获取所有日志
  };
  const handleCheck = () => {
    setOpen(true);
  };
  const LightController = (props) => {
    const [lightness, setLightNess] = useState(0);
    const { deviceId, status } = props;
    const changeLightness = () => {
      axios({
        url: 'http://localhost:9000/device/change',
        method: 'GET',
        params: {
          ['type']: 'light_bulb',
          ['deviceId']: deviceId,
          ['lightness']: lightness,
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });
    };
    const closeLight = () => {
      axios({
        url: 'http://localhost:9000/device/change',
        method: 'GET',
        params: {
          ['type']: 'light_bulb',
          ['deviceId']: deviceId,
          ['lightness']: 0,
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });
    };
    const openLight = () => {
      axios({
        url: 'http://localhost:9000/device/change',
        method: 'GET',
        params: {
          ['type']: 'light_bulb',
          ['deviceId']: deviceId,
          ['lightness']: 100,
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });
    };

    return (
      <Grid
        container
        spacing={3}
        sx={{
          marginLeft: 'calc(20%)',
          marginTop: '10px',
        }}>
        <Grid item md={6} xs={12}>
          <TextField
            fullWidth
            helperText='请输入你要修改的灯的亮度'
            label='lightness'
            name='lightness'
            onChange={(e) => {
              setLightNess(e.target.value);
            }}
            required
            value={lightness}
            variant='outlined'
          />
        </Grid>
        <Grid
          container
          sx={{
            marginLeft: '10%',
          }}>
          <Grid>
            <Button onClick={changeLightness}>提交</Button>
          </Grid>
          <Grid>
            <Button onClick={status ? closeLight : openLight}>
              {status ? '关灯' : '开灯'}
            </Button>
          </Grid>
        </Grid>
      </Grid>
    );
  };
  const DoorController = (props) => {
    const { deviceId, status } = props;
    console.log(deviceId);
    const DeviceId = toString(deviceId);
    const closeDoor = () => {
      axios({
        url: 'http://localhost:9000/device/change',
        method: 'GET',
        params: {
          ['type']: 'door',
          ['deviceId']: deviceId,
          ['target']: 'false',
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });
    };
    const openDoor = () => {
      axios({
        url: 'http://localhost:9000/device/change',
        method: 'GET',
        params: {
          ['type']: 'door',
          ['deviceId']: `${deviceId}`,
          ['target']: 'true',
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });
    };

    return (
      <Box
        sx={{
          marginTop: '2em',
          display: 'flex',
          alignItems: 'center',
          justifyContent: 'center',
          marginLeft: 'calc(50% - 2em)',
        }}>
        <Grid container spacing={3}>
          <Grid>
            <Button onClick={status ? closeDoor : openDoor}>
              {status ? '关门' : '开门'}
            </Button>
          </Grid>
        </Grid>
      </Box>
    );
  };
  const SwitchController = (props) => {
    const { deviceId, status } = props;
    console.log(deviceId);
    const DeviceId = toString(deviceId);
    const closeSwitch = () => {
      axios({
        url: 'http://localhost:9000/device/change',
        method: 'GET',
        params: {
          ['type']: 'switch',
          ['deviceId']: deviceId,
          ['target']: 'false',
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });
    };
    const openSwitch = () => {
      axios({
        url: 'http://localhost:9000/device/change',
        method: 'GET',
        params: {
          ['type']: 'switch',
          ['deviceId']: `${deviceId}`,
          ['target']: 'true',
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });
    };

    return (
      <Box
        sx={{
          marginTop: '2em',
          display: 'flex',
          alignItems: 'center',
          justifyContent: 'center',
          marginLeft: 'calc(50% - 2em)',
        }}>
        <Grid container spacing={3}>
          <Grid>
            <Button onClick={status ? closeSwitch : openSwitch}>
              {status ? '关' : '开'}
            </Button>
          </Grid>
        </Grid>
      </Box>
    );
  };
  const SensorController = (props) => {
    const [value, setValue] = useState(0);
    const { deviceId, status } = props;
    const changeValue = () => {
      axios({
        url: 'http://localhost:9000/device/change',
        method: 'GET',
        params: {
          ['type']: 'sensor',
          ['deviceId']: deviceId,
          ['value']: value,
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });
    };


    return (
      <Grid
        container
        spacing={3}
        sx={{
          marginLeft: 'calc(20%)',
          marginTop: '10px',
        }}>
        <Grid item md={6} xs={12} sx={{
          marginL: '-3em'
        }}>
          <TextField
            fullWidth
            helperText='请输入你的目标温度/湿度'
            label='value'
            name='value'
            onChange={(e) => {
              setValue(e.target.value);
            }}
            required
            value={value}
            variant='outlined'
          />
        </Grid>
        <Grid
          container
          sx={{
            marginLeft: '10%',
          }}>
          <Grid>
            <Button onClick={changeValue} sx={{
              marginL: '-3em'
            }}>提交</Button>
          </Grid>
        </Grid>
      </Grid>
    );
  };
  return (
    <Box component='div'>
      {loading ? (
        <></>
      ) : (
        <Dialog open={deviceDetailOpen} onClose={handleClose}>
          <DialogTitle>设备信息</DialogTitle>
          <DialogContent>
            <Card>
              <CardHeader subheader='设备信息查看' title='设备信息' />
              <Divider />
              <CardContent>
                <Grid container spacing={3}>
                  <Grid item md={6} xs={12}>
                    <MyTextField
                      style={{ WebkitTextFillColor: 'black!important' }}
                      fullWidth
                      label='设备名称'
                      name='firstName'
                      required
                      value={deviceInfo.deviceName}
                      variant='outlined'
                      disabled
                    />
                  </Grid>
                  <Grid item md={6} xs={12}>
                    <MyTextField
                      style={{ WebkitTextFillColor: 'black!important' }}
                      fullWidth
                      label='设备描述'
                      name='firstName'
                      required
                      value={deviceInfo.description}
                      variant='outlined'
                      disabled
                    />
                  </Grid>
                  <Grid item md={6} xs={12}>
                    <MyTextField
                      style={{ WebkitTextFillColor: 'black!important' }}
                      fullWidth
                      label='设备类型'
                      name='firstName'
                      required
                      // TODO 根据类型设置展示值（比如亮度，温度等）
                      value={deviceInfo.type}
                      variant='outlined'
                      disabled
                    />
                  </Grid>
                  <Grid item md={6} xs={12}>
                    <MyTextField
                      style={{ WebkitTextFillColor: 'black!important' }}
                      fullWidth
                      label='设备状态'
                      name='firstName'
                      required
                      value={
                        (deviceInfo.type === 'door' || deviceInfo.type === 'switch')
                          ? deviceInfo.status
                            ? '开着'
                            : '关闭'
                          : deviceInfo.type === 'light_bulb'
                            ? `亮度：` + deviceInfo.brightness
                            : deviceInfo.type === 'wet'
                              ? `湿度` + deviceInfo.sensorValue
                              : `温度` + deviceInfo.sensorValue
                      }
                      variant='outlined'
                      disabled
                    />
                  </Grid>
                </Grid>
              </CardContent>
            </Card>
            {open ? (
              deviceInfo.type === 'door' ? (
                <DoorController
                  deviceId={deviceid}
                  status={deviceInfo.status}
                />
              ) : deviceInfo.type === 'light_bulb' ? (
                <LightController
                  deviceId={deviceid}
                  status={deviceInfo.status}
                />
              ) : deviceInfo.type === 'switch' ? (<SwitchController deviceId={deviceid} status={deviceInfo.status}></SwitchController>) : (deviceInfo.type === 'temperature' || deviceInfo.type ===
                'wet') ? (<SensorController deviceId={deviceid} status={deviceInfo.status}></SensorController>) : (<></>)
            ) : (
              <></>
            )}
          </DialogContent>
          <DialogActions>
            <Button onClick={handleCheck}>查看详情</Button>
            <Button onClick={handleClose}>关闭</Button>
          </DialogActions>
        </Dialog>
      )}
    </Box>
  );
}
