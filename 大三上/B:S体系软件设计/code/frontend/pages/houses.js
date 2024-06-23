import { useSelector, useDispatch } from 'react-redux';
import { useEffect, useState } from 'react';
import { DashboardNavbar } from '../components/DashNavBar';
import SideBar from '../components/DashSideBar';
import { DashBoardWrapper } from './dashboard';
import OtherHousesIcon from '@mui/icons-material/OtherHouses';
import DownloadIcon from '@mui/icons-material/Download';
import DeleteForeverIcon from '@mui/icons-material/DeleteForever';
import Router from 'next/router';
import { setHouseID } from '../redux/house.slice';
import {
  Box,
  Typography,
  Button,
  Grid,
  Card,
  CardContent,
  Avatar,
  Divider,
  Link,
} from '@mui/material';
import axios from 'axios';
import NewHouseForm from '../components/NewHouseForm';
export default function Rooms() {
  const dispatch = useDispatch();
  const [open, setOpen] = useState(false);
  const addRoom = () => {
    setOpen(true);
  };
  const userid = useSelector((state) => state.userID.value);
  const [loading, setLoading] = useState(true);
  let [houses, setHouses] = useState([]);
  let [isDeleting, setIsDeleting] = useState(false);
  useEffect(() => {
    (async function run() {
      console.log('in axios');
      await axios({
        url: 'http://localhost:9000/house/all',
        method: 'GET',
        params: {
          userid: userid,
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          // console.log('res.data.result', res.data.result);
          // console.log('houses', houses);
          setHouses(res.data.result);
          setLoading(false);
        })
        .catch((error) => {
          console.log(error);
        });
    })();
  }, [userid, open, isDeleting]);
  console.log(houses);
  const handleClick = (house) => {
    dispatch(setHouseID(parseInt(house.houseId)));
    Router.push('/manageRoom');
  };
  const handleDelete = (house) => {
    const houseid = house.houseId;
    (async function run() {
      console.log('in axios');
      await axios({
        url: 'http://localhost:9000/house/delete',
        method: 'GET',
        params: {
          houseid: houseid,
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          // console.log('res.data.result', res.data.result);
          // console.log('houses', houses);
          setIsDeleting(!isDeleting);
        })
        .catch((error) => {
          console.log(error);
        });
    })();
  };
  return (
    <div>
      <DashboardNavbar onSidebarOpen={false} key='navbar  ' />{' '}
      <SideBar key='sidebar' />
      {/* 顶栏 */}
      <DashBoardWrapper>
        <Box
          sx={{
            marginLeft: '0',
            '@media(min-width: 980px)': {
              marginLeft: '300px',
            },
            zIndex: '200',
            width: '100%',
          }}
          component='main'>
          <Box
            sx={{
              alignItems: 'center',
              display: 'flex',
              justifyContent: 'space-between',
              flexWrap: 'wrap',
              m: -1,
            }}>
            <Typography sx={{ m: 1, marginTop: '30px' }} variant='h3'>
              管理场所
            </Typography>
            <Box
              sx={{
                m: 1,
              }}>
              <Button
                color='primary'
                variant='contained'
                sx={{
                  marginRight: '1vw',
                }}
                onClick={addRoom}>
                添加场所
              </Button>
            </Box>
          </Box>
        </Box>
      </DashBoardWrapper>
      <Divider />
      <NewHouseForm open={open} setOpen={setOpen} />
      {loading ? (
        <></>
      ) : (
        <Box
          sx={{
            marginLeft: '0',
            maxWidth: 'calc(100vw)',
            '@media(min-width: 980px)': {
              marginLeft: '320px',
              maxWidth: 'calc(100vw - 350px)',
            },
            zIndex: '200',
            width: '100%',
            marginTop: '30px',
          }}>
          <Grid
            container
            spacing={3}
            rowSpacing={1}
            sx={{
              flexWrap: 'wrap',
            }}>
            {houses.map((house) => {
              return (
                <Grid item key={house.houseId} xs={6}>
                  <Card
                    display='flex'
                    height='100%'
                    sx={{
                      flexDirection: 'column',
                      backgroundColor: '#ffffff',
                    }}>
                    <CardContent
                      sx={{
                        maxHeight: '20em',
                        minHeight: '20em',
                        height: '20em',
                        overflowY: 'hidden',
                      }}>
                      <Box
                        sx={{
                          display: 'flex',
                          justifyContent: 'center',
                        }}>
                        <Avatar variant='square'>
                          <OtherHousesIcon
                            fontSize='large'
                            sx={{
                              fill: '#white',
                            }}
                          />
                        </Avatar>
                      </Box>
                      <Typography
                        align='center'
                        color='textPrimary'
                        gutterBottom
                        variant='h5'>
                        {house.houseName}
                      </Typography>
                      <Divider />
                      <Typography
                        align='left'
                        color='textPrimary'
                        gutterBottom
                        variant='h5'>
                        &nbsp;&nbsp;&nbsp;&nbsp;{house.description}
                      </Typography>
                    </CardContent>
                    <Box sx={{ flexGrow: 1 }} />
                    <Divider />
                    <Box>
                      <Grid
                        container
                        spacing={2}
                        sx={{
                          justifyContent: 'space-between',
                        }}
                        wrap='wrap'>
                        <Grid
                          item
                          sx={{
                            alignItems: 'center',
                            display: 'flex',
                            minHeight: '100px',
                            flexDirection: 'row',
                            justifyContent: 'center',
                            alignItems: 'center',
                            marginLeft: '30px',
                          }}>
                          {/* <Link href={`/manageRoom`}> */}
                          <Button
                            startIcon={<DownloadIcon fontSize='small' />}
                            sx={{ mr: 1 }}
                            onClick={() => handleClick(house)}>
                            查看房间
                          </Button>
                          <Button
                            startIcon={<DeleteForeverIcon fontSize='small' />}
                            sx={{ mr: 1 }}
                            onClick={() => handleDelete(house)}>
                            删除场所
                          </Button>
                          {/* </Link> */}
                        </Grid>
                        <Grid
                          item
                          sx={{
                            alignItems: 'center',
                            display: 'flex',
                            flexDirection: 'column-reverse',
                            justifyContent: 'center',
                          }}>
                          {/* <Box
                          sx={{
                            display: 'column-reverse',
                            alignItems: 'center',
                            justifyContent: 'center',
                          }}> */}
                          <Box
                            sx={{
                              color: 'actions.hover',
                            }}>
                            <Typography
                              color='textSecondary'
                              display='inline'
                              variant='h5'>
                              拥有房间数:{house.roomcount}
                            </Typography>
                            <OtherHousesIcon
                              fontSize='large'
                              sx={{
                                marginBottom: '-5px',
                              }}
                            />
                          </Box>
                        </Grid>
                      </Grid>
                    </Box>
                  </Card>
                </Grid>
              );
            })}
          </Grid>
        </Box>
      )}
    </div>
  );
}
