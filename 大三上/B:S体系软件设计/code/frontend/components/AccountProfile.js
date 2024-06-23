import {
  Avatar,
  Box,
  Button,
  Card,
  CardActions,
  CardContent,
  Divider,
  Typography,
} from '@mui/material';
import { useSelector } from 'react-redux';
import { useEffect, useState } from 'react';
export const AccountProfile = () => {
  const [user, setUser] = useState({ avatar: 'avatar.png' });
  const userName = useSelector((state) => state.userName.value);
  useEffect(() => {
    setUser({
      ...user,
      username: userName,
    });
  }, []);
  return (
    <Card>
      <CardContent>
        <Box
          sx={{
            alignItems: 'center',
            display: 'flex',
            flexDirection: 'column',
          }}>
          <Avatar
            src={user.avatar}
            sx={{
              height: 64,
              mb: 2,
              width: 64,
            }}
          />
          <Typography color='textPrimary' gutterBottom variant='h5'>
            {user.username}
          </Typography>
        </Box>
      </CardContent>
      <Divider />
    </Card>
  );
};
