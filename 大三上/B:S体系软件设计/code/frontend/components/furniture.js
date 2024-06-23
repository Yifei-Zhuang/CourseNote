import React from 'react';
import { useDrag } from 'react-dnd';
import { ItemTypes } from './Types';
import { Grid, Box } from '@mui/material';
export default function Furniture(props) {
  const { name, sourceType, ...other } = props;
  const [{ isDragging }, drag] = useDrag(() => ({
    type: sourceType,
    collect: (monitor) => ({
      isDragging: !!monitor.isDragging(),
    }),
    item: () => {
      // console.log(sourceType);
      //! 对应家具的类型，可以在ItemTypes中找到原型
      return { isDragging: isDragging, type: sourceType };
    },
  }));
  return (
    <Box
      ref={drag}
      component={'img'}
      sx={{
        height: '40px',
        opacity: isDragging ? 0.5 : 1,
        cursor: 'move',
      }}
      src={name}
      alt='cannot load svg'
      {...other}></Box>
  );
}
