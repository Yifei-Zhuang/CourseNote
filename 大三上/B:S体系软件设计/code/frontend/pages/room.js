import { Box, Divider, Typography } from '@mui/material';
import { useEffect, useState } from 'react';
import React from 'react';
import { DashboardNavbar } from '../components/DashNavBar';
import SideBar from '../components/DashSideBar';
import { DashBoardWrapper } from './dashboard';
import { Grid, Button, Alert } from '@mui/material';
import { useDrop } from 'react-dnd';
const BlockWidth = '5%';
const BlockHeight = '5%';
import Image from 'next/image';
import Furniture from '../components/furniture';
import { ItemTypes } from '../components/Types';
import NewDeviceForm from '../components/NewDeviceForm';
import { useDispatch, useSelector } from 'react-redux';
import { setShow as higherSetShow } from '../redux/show.slice';
import { setType as higherSetType } from '../redux/dragtype.slice';
import { setPosition as higherSetPosition } from '../redux/position.slice';
import AnotherNewDeviceForm from '../components/AnotherNewDeviceForm';
import axios from 'axios';
import DeviceList from '../components/DeviceList';
import DeviceDetail from '../components/DeviceDetail';
import { setDeviceId } from '../redux/deviceId.slice';

const TempBlock = (props) => {
  const { index, setNewDeviceOpen } = props;
  const dispatch = useDispatch();
  let setShow = (value) => {
    dispatch(higherSetShow(value));
  };
  let setType = (type) => {
    dispatch(higherSetType(type));
  };
  let setPosition = (position) => {
    dispatch(higherSetPosition(position));
  };
  let [{ isOver }, drop] = useDrop(
    () => ({
      accept: [
        ItemTypes.furniture,
        ItemTypes.door,
        ItemTypes.light_bulb,
        ItemTypes.wet,
        ItemTypes.temperature,
        ItemTypes.switch
      ],
      drop: (item, monitor) => {
        setType(item.type);
        setShow(true);
        setNewDeviceOpen(true);
        setPosition(index);
      },
      collect: (monitor) => ({
        isOver: !!monitor.isOver(),
      }),
    }),
    [],
  );
  return (
    <Box
      ref={drop}
      // position={'absolute'}
      sx={{
        backgroundColor: 'black',
        width: BlockWidth,
        height: BlockHeight,
        backgroundColor: 'transparent',
        // visibility: 'hidden',
        opacity: '1',
        // border: 1,
      }}
      zIndex='300'>
      {isOver && (
        <div
          style={{
            // position: 'absolute',
            // top: 0,
            // left: 0,
            height: '100%',
            width: '100%',
            zIndex: 9998,
            opacity: 0.5,
            backgroundColor: 'yellow',
          }}
        />
      )}
    </Box>
  );
};
// 查看单个房间
export default function room() {
  const [imgWidth, setImgWidth] = React.useState(0);
  const houseId = useSelector((state) => state.houseID.value);
  const userID = useSelector((state) => state.userID.value);
  const roomid = useSelector((state) => state.room.value);
  const [newDeviceOpen, setNewDeviceOpen] = useState(false);
  // 用来处理useeffect异步执行问题
  const [isLoading, setIsLoading] = useState(true);
  // 用来删除设备的时候，出发useeffect执行，实现设备列表等刷新
  const [isDeleting, setIsDeleting] = useState(false);
  const [image, setImage] = useState(null);
  const [noImage, setNoImage] = useState(false);
  const [uploadSuccess, setUploadSuccess] = useState(false);

  const [deviceDetailOpen, setDeviceDetailOpen] = useState(false);
  const mySetImage = (image) => {
    return new Promise((resolve, reject) => {
      setImage(image);
      resolve();
    });
  };
  // 实现图片拖动必须的组件
  let blocks = [];
  const convertBase64 = (file) => {
    return new Promise((resolve, reject) => {
      const fileReader = new FileReader();
      fileReader.readAsDataURL(file);
      fileReader.onload = () => {
        resolve(fileReader.result);
      };
      fileReader.onerror = (error) => {
        reject(error);
      };
    });
  };
  // TODO 户型图上传
  const onImgChange = async (event) => {
    console.log('file', event.target.files[0]);
    let file = event.target.files[0];
    const temp = await convertBase64(file);
    event.preventDefault();
    let payload = {
      ['image']: temp,
      ['roomId']: parseInt(roomid),
    };
    axios({
      url: 'http://localhost:9000/image/upload',
      method: 'POST',
      data: {
        ...payload,
      },
      withCredentials: true,
      headers: {
        Accept: 'application/json',
        'Content-Type': 'application/json',
      },
    })
      .then((res) => {
        console.log(res);
        setUploadSuccess(true);
        setTimeout(() => setUploadSuccess(false), 5000);
      })
      .catch((err) => {
        console.log(err);
      });
  };
  // 当前房间的信息需要动态获取
  const [room, setRoom] = useState({});

  let [devicelist, setDeviceList] = useState([]);
  useEffect(() => {
    //TODO 从后端获取图片
    (async function run() {
      console.log('get room info');
      console.log('room id is ', roomid);
      await axios({
        url: 'http://localhost:9000/room/get',
        method: 'GET',
        params: {
          ['roomid']: roomid,
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          setRoom(res.data.result[0]);
        })
        .catch((error) => {
          console.log('fetch room info', error);
        });
      await axios({
        url: 'http://localhost:9000/device/get',
        method: 'GET',
        params: {
          ['roomid']: roomid,
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          setDeviceList(res.data.result);
        })
        .catch((error) => {
          console.log('fetch device', error);
        });
      await axios({
        method: 'GET',
        url: 'http://localhost:9000/image/get',
        params: {
          ['roomid']: roomid,
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      }).then(async (res) => {
        const result = res.data;
        if (!result.status) {
          console.log('error', res);
          setNoImage(true);
          setTimeout(() => {
            setNoImage(false);
          }, 5000);
        } else {
          mySetImage(result.image);
        }
      });
      console.log('room', room);
      console.log('devicelist', devicelist);
    })();
  }, [isDeleting, newDeviceOpen, roomid]);
  useEffect(() => {
    setIsLoading(false);
  }, [image]);
  for (let i = 0; i < 400; i++) {
    blocks.push(
      <TempBlock index={i} key={i} setNewDeviceOpen={setNewDeviceOpen} />,
    );
  }
  return (
    <div>
      {noImage ? (
        <Alert
          sx={{
            marginLeft: '0',
            '@media(min-width: 980px)': {
              marginLeft: '3px',
            },
          }}
          severity='error'>
          请先上传户型图
        </Alert>
      ) : (
        <></>
      )}
      {uploadSuccess ? (
        <Alert
          sx={{
            marginLeft: '0',
            '@media(min-width: 980px)': {
              marginLeft: '300px',
            },
          }}
          severity='success'>
          图片上传成功！
        </Alert>
      ) : (
        <></>
      )}

      <DashboardNavbar onSidebarOpen={false} key='navbar' />
      <SideBar key='sidebar' />
      <DashBoardWrapper>
        <Box
          sx={{
            marginLeft: '0',
            '@media(min-width: 980px)': {
              marginLeft: '300px',
            },
            paddingTop: 'calc(-5%)',
            zIndex: '200',
            width: '100%',
          }}
          variant='main'>
          <Box
            sx={{
              display: 'flex',
            }}
            alignContent={'center'}
            justifyContent={'center'}>
            <Typography variant='h5' color='primary.main'>
              {room.name}
            </Typography>
          </Box>
          <Box
            sx={{
              display: 'flex',
            }}
            alignContent={'center'}
            justifyContent={'center'}
          // component='input'
          // type={'file'}
          >
            <Button component='label'>
              上传户型图
              <input
                type='file'
                hidden
                onChange={(target) => onImgChange(target)}
              />
            </Button>
          </Box>
          <Divider />
          <Grid container spacing={10} justifyContent={'space-evenly'}>
            <Grid item>
              <Typography variant='subtitle1' display={'inline-block'}>
                门
              </Typography>
              <Furniture name='door_closed.svg' sourceType={ItemTypes.door} />
            </Grid>
            <Grid item>
              <Typography variant='subtitle1' display={'inline-block'}>
                电灯泡
              </Typography>
              <Furniture
                name='opened_light.svg'
                sourceType={ItemTypes.light_bulb}
              />
            </Grid>
            <Grid item>
              <Typography variant='subtitle1' display={'inline-block'}>
                湿度传感器
              </Typography>
              <Furniture name='wetty.svg' sourceType={ItemTypes.wet} />
            </Grid>
            <Grid item>
              <Typography variant='subtitle1' display={'inline-block'}>
                温度传感器
              </Typography>
              <Furniture name='temp.svg' sourceType={ItemTypes.temperature} />
            </Grid>
            <Grid item>
              <Typography variant='subtitle1' display={'inline-block'}>
                开关
              </Typography>
              <Furniture name='switch_on.svg' sourceType={ItemTypes.switch} />
            </Grid>
          </Grid>
          {isLoading ? (
            <></>
          ) : (
            <Box
              sx={{
                display: 'flex',
                alignItems: 'center',
                justifyContent: 'end',
                marginRight: '20%',
                width: '100%',
                position: 'relative',
                height: 'calc(100vh - 100px)',
              }}>
              {/* 表单 默认隐藏 */}
              {/*  houseid, userid */}
              <AnotherNewDeviceForm
                open={newDeviceOpen}
                setOpen={setNewDeviceOpen}
              />
              {/* <NewDeviceForm
              houseid={houseId}
              userid={userID}
              open={newDeviceOpen}
              setOpen={setNewDeviceOpen}
            /> */}
              {/* 图片位置 */}
              {/* 切片起始位置 */}
              <Box
                position={'absolute'}
                display={'flex'}
                // flexWrap
                width={'100%'}
                height={'100%'}
                top={0}
                left={0}
                sx={{
                  flexWrap: 'wrap',
                  marginLeft: '20px',
                }}
                zIndex={9998}>
                {blocks}
              </Box>
              <Box
                position={'absolute'}
                display={'flex'}
                // flexWrap
                width={'100%'}
                height={'100%'}
                top={0}
                left={0}
                sx={{
                  flexWrap: 'wrap',
                  marginLeft: '20px',
                }}
                zIndex={300}>
                {devicelist.map((item) => {
                  {
                    console.log('item', item);
                    let name = 'refrigerator.svg';
                    switch (item.type) {
                      case 'light_bulb': {
                        if (item.status) {
                          name = 'opened_light.svg';
                        } else {
                          name = 'closed_light.svg';
                        }
                        break;
                      }
                      case 'door': {
                        if (item.status) {
                          name = 'door_opened.svg';
                        } else {
                          name = 'door_closed.svg';
                        }
                        break;
                      }
                      case 'wet': {
                        name = 'wetty.svg';
                        break;
                      }
                      case 'temperature': {
                        name = 'temp.svg';
                        break;
                      }
                      case 'switch':
                        if (item.status) {
                          name = 'switch_on.svg';
                        } else {
                          name = 'switch_off.svg';
                        }
                        break;
                    }
                    return (
                      <Box
                        key={parseInt(item.position) + 200}
                        onClick={() => {
                          console.log('clicked')
                          // const deviceid = item.deviceId;
                          // dispatch(setDeviceId(deviceid));
                          // setDeviceDetailOpen(true);
                        }}
                        // backgroundColor={'white'}
                        component={'img'}
                        sx={{
                          zIndex: 9999,
                          position: 'absolute',
                          top: `calc(5% * ${item.position / 20})`,
                          left: `calc(5%*${item.position % 20})`,
                          height: name === 'anotherdoor.svg' || name === 'door_closed.svg' ? '80px' : '80px',
                          width: name === 'anotherdoor.svg' || name === 'door_closed.svg' ? '80px' : '80px',
                        }}
                        src={name}
                        alt='cannot load svg'
                      >
                      </Box>
                    );
                  }
                })}
              </Box>
              <Box
                sx={{
                  width: 'calc(100vw)',
                  '@media(min-width:980px)': {
                    width: 'calc(100vw - 320px)',
                  },
                  height: 'calc(100vh - 100px)',
                  objectFit: 'fill',
                }}
                component='img'
                src={`data:image/png;base64,${image}`}
                zIndex={200}
              />
            </Box>
          )}
        </Box>
      </DashBoardWrapper>

      {isLoading ? (
        <></>
      ) : (
        <Box
          sx={{
            '@media(min-width: 980px)': {
              marginLeft: '350px',
            },
          }}>
          <DeviceList
            sx={{
              marginLeft: '0',
              '@media(min-width: 980px)': {
                marginLeft: '350px',
                width: 'calc(100vw-350px)',
              },
              zIndex: '200',
              width: '100%',
            }}
            devicelist={devicelist}
            isDeleting={isDeleting}
            setIsDeleting={setIsDeleting}
            setDeviceDetailOpen={setDeviceDetailOpen}
          />
          <DeviceDetail
            deviceDetailOpen={deviceDetailOpen}
            setDeviceDetailOpen={setDeviceDetailOpen}
          />
        </Box>
      )}
    </div>
  );
}
