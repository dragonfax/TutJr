
const byte level1_wall_data [] = {

    
        
        B11111111,
    
        
        B11111111,
    
        
        B11111111,
    
        
        B11100000,
    

    
        
        B10000000,
    
        
        B00101000,
    
        
        B10000000,
    
        
        B00100000,
    

    
        
        B11000010,
    
        
        B10101010,
    
        
        B11101010,
    
        
        B00100000,
    

    
        
        B10000010,
    
        
        B10101010,
    
        
        B00000010,
    
        
        B00100000,
    

    
        
        B10111011,
    
        
        B10101110,
    
        
        B11100011,
    
        
        B10100000,
    

    
        
        B10000000,
    
        
        B10101000,
    
        
        B00000000,
    
        
        B00100000,
    

    
        
        B10001000,
    
        
        B10101010,
    
        
        B00111111,
    
        
        B10100000,
    

    
        
        B10000000,
    
        
        B10000010,
    
        
        B00000000,
    
        
        B00100000,
    

    
        
        B10111110,
    
        
        B10001010,
    
        
        B10111110,
    
        
        B00100000,
    

    
        
        B10000000,
    
        
        B00000000,
    
        
        B10001000,
    
        
        B00100000,
    

    
        
        B10111010,
    
        
        B11111000,
    
        
        B10001110,
    
        
        B10100000,
    

    
        
        B10001010,
    
        
        B00000000,
    
        
        B10001000,
    
        
        B10100000,
    

    
        
        B11101110,
    
        
        B00111011,
    
        
        B11101000,
    
        
        B10100000,
    

    
        
        B10001000,
    
        
        B00100000,
    
        
        B00000000,
    
        
        B00100000,
    

    
        
        B11111111,
    
        
        B11111111,
    
        
        B11111111,
    
        
        B11100000,
    

};

const Monster level1_monsters [] = {

    Monster(MapPos(17,1)), 

    Monster(MapPos(18,1)), 

    Monster(MapPos(7,3)), 

    Monster(MapPos(17,5)), 

    Monster(MapPos(5,11)), 

    Monster(MapPos(21,11)), 

    Monster(MapPos(11,13)), 

};

const Door level1_doors [] = {

    Door(MapPos(4, 2), VERTICAL),

    Door(MapPos(24, 2), VERTICAL),

    Door(MapPos(20, 4), VERTICAL),

    Door(MapPos(2, 6), HORIZONTAL),

    Door(MapPos(6, 6), VERTICAL),

    Door(MapPos(16, 6), VERTICAL),

    Door(MapPos(10, 8), VERTICAL),

    Door(MapPos(24, 8), HORIZONTAL),

    Door(MapPos(14, 10), VERTICAL),

    Door(MapPos(18, 10), VERTICAL),

    Door(MapPos(8, 12), HORIZONTAL),

    Door(MapPos(22, 12), HORIZONTAL),

};

const Key level1_keys [] = {

    Key(MapPos(21, 9)),

};

const Gate level1_gates [] = {

    Gate(MapPos(2, 13)),

};

Level level = Level(
  27, // width
  15, // height
  4, // row_width ( in bytes )
  level1_wall_data,
  7, // num monsters
  level1_monsters,
  12, // num doors
  level1_doors,
  1,
  level1_keys,
  1,
  level1_gates,
  Exit(MapPos(1,13)),
  Entrance(MapPos(11,1))
);
