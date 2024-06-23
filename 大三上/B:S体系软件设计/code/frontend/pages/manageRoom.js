import SideBar from '../components/DashSideBar';
import { DashBoardWrapper } from './dashboard';
import { DashboardNavbar } from '../components/DashNavBar';
import { Typography, Box, Button } from '@mui/material';
import RoomList from '../components/RoomList';
import { useEffect, useState } from 'react';
import NewRoomForm from '../components/NewRoomForm';
import { useSelector } from 'react-redux';
import axios from 'axios';
// 管理当前场所(houseid)的所有的room
export default function manageRoom() {
  const houseid = useSelector((state) => state.houseID.value);
  const [loading, setLoading] = useState(true);
  const [roomList, setRoomList] = useState([]);
  const [open, setOpen] = useState(false);
  const [isDeleting, setIsDeleting] = useState(false);
  useEffect(() => {
    (async function run() {
      console.log('in axios');
      await axios({
        url: 'http://localhost:9000/room/all',
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
          setRoomList(res.data.result);
          // console.log('rooms', roomList);
          setLoading(false);
        })
        .catch((error) => {
          console.log(error);
        });
    })();
  }, [houseid, open, isDeleting]);
  console.log(roomList);
  const addRoom = () => {
    setOpen(true);
  };

  return (
    <div>
      <DashboardNavbar onSidebarOpen={false} key='navbar  ' />{' '}
      <SideBar key='sidebar' />
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
              管理房间
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
                添加房间
              </Button>
            </Box>
          </Box>
          {loading ? (
            <></>
          ) : (
            <RoomList
              rooms={roomList}
              isDeleting={isDeleting}
              setIsDeleting={setIsDeleting}
            />
          )}
        </Box>
      </DashBoardWrapper>
      {loading ? <></> : <NewRoomForm open={open} setOpen={setOpen} />}
    </div>
  );
}
