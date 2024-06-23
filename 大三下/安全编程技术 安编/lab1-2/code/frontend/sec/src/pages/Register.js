import * as React from 'react';
import Button from '@mui/material/Button';
import CssBaseline from '@mui/material/CssBaseline';
import TextField from '@mui/material/TextField';
import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import Container from '@mui/material/Container';
import axios from 'axios';
import {useStorage} from '../utils/LocalStorageUtil'
import {useNavigate} from 'react-router-dom'

export default function SignIn() {
    const store = useStorage();
    const navigate = useNavigate();
    const handleSubmit = (event) => {
        event.preventDefault();
        const formdata = new FormData(event.currentTarget);
        const data = {
            "username": formdata.get("username"),
            "password": formdata.get("password")
        }
        axios.post('http://localhost:8080/register', data).then(res => {
            console.log(res);
            navigate("/login")
        }).catch(e => {
            console.log(e);
            alert(e)
        })
    };

    return (
        <Container component="main" maxWidth="xs">
            <CssBaseline/>
            <Box
                sx={{
                    marginTop: 8,
                    display: 'flex',
                    flexDirection: 'column',
                    alignItems: 'center',
                }}
            >
                <Typography component="h1" variant="h5">
                    注册
                </Typography>
                <Box component="form" onSubmit={handleSubmit} noValidate sx={{mt: 1}}>
                    <TextField
                        margin="normal"
                        required
                        fullWidth
                        id="username"
                        label="用户名"
                        name="username"
                        autoComplete="username"
                        autoFocus
                    />
                    <TextField
                        margin="normal"
                        required
                        fullWidth
                        name="password"
                        label="密码"
                        type="password"
                        id="password"
                        autoComplete="current-password"
                    />
                    <Button
                        type="submit"
                        fullWidth
                        variant="contained"
                        sx={{mt: 3, mb: 2}}
                    >
                        注册
                    </Button>
                </Box>
            </Box>
        </Container>
    );
}