class MazeBuilder{

    constructor(size){
        this.numOfCells = size;
        this.sizeOfMaze = (size*2)+1;
        this.startxcoordwall = null;
        this.endxcoordwall = null;
        this.maze_matrix = []; //char
        this.coordinate_matrix = []; //bool
        this.constructMatricies();
        this.makeMaze(this.startxcoordwall,1);
        this.updateMazeDOMElements();
        this.directions = []; //string

        this.solver(this.startxcoordwall,0,true,false,false,false,0);


        this.row_size = null;
        this.col_size = null;
        this.lastk = null;
        

        //booleans
        this.deadend = false;
        this.atend = false;

        //lists
        
        
        
    }

    constructMatricies(){
        for(let i = 0; i < this.sizeOfMaze; i++){
            this.maze_matrix.push([]);
            this.coordinate_matrix.push([]);
            for(let j = 0; j < this.sizeOfMaze; j++){
                this.coordinate_matrix[i].push(false);
                if((i%2==0)||(i==0)){
                    this.maze_matrix[i].push('#');
                }else if((j%2==0)||(j==0)){
                    this.maze_matrix[i].push('#');
                }else{
                    this.maze_matrix[i].push(' ');
                }
            }
        }
        this.startxcoordwall = this.randomOddNumberGeneratorForMazeBlock();
        this.endxcoordwall = this.randomOddNumberGeneratorForMazeBlock();
        this.maze_matrix[this.startxcoordwall][0] = ' ';
        this.maze_matrix[this.endxcoordwall][this.sizeOfMaze-1] = ' ';
        this.coordinate_matrix[this.startxcoordwall][1] = true;
    }

    //ret int
    randomOddNumberGeneratorForMazeBlock(){
        let returnInt = 0;
        let isOdd = false;
        while(!isOdd){
            returnInt = Math.floor(Math.random() * (this.sizeOfMaze-2));
            if(returnInt != 1){
                isOdd = (returnInt%2 != 0);
            }else{
                isOdd = true;
            }
        }
        return returnInt;
    }

    makeMaze(xcoor,ycoor){
        let nor = this.canGoNorth(xcoor,ycoor);
        let sou = this.canGoSouth(xcoor,ycoor);
        let eas = this.canGoEast(xcoor,ycoor);
        let wes = this.canGoWest(xcoor,ycoor);

        if(!nor && !sou && !eas && !wes){
            //break case
        }else{
            let hasMoved = false;
            while(!hasMoved){
                let res = Math.floor(Math.random() * 4);
                switch(res){
                    case 0:
                        if(nor){
                            this.coordinate_matrix[xcoor-2][ycoor] = true;
                            this.maze_matrix[xcoor-1][ycoor] = ' ';
                            hasMoved = true;
                            this.makeMaze(xcoor-2,ycoor);
                        }
                        break;
                    case 1:
                        if(sou){
                            this.coordinate_matrix[xcoor+2][ycoor] = true;
                            this.maze_matrix[xcoor+1][ycoor] = ' ';
                            hasMoved = true;
                            this.makeMaze(xcoor+2,ycoor);
                        }
                        break;
                    case 2:
                        if(eas){
                            this.coordinate_matrix[xcoor][ycoor+2] = true;
                            this.maze_matrix[xcoor][ycoor+1] = ' ';
                            hasMoved = true;
                            this.makeMaze(xcoor,ycoor+2);
                        }
                        break;
                    case 3:
                        if(wes){
                            this.constructMatricies[xcoor][ycoor-2] = true;
                            this.maze_matrix[xcoor][ycoor-1] = ' ';
                            hasMoved = true;
                            this.makeMaze(xcoor,ycoor-2);
                        }
                        break;
                }
            }
            this.makeMaze(xcoor,ycoor);
        }
    }

    //int int
    //ret bool
    canGoNorth(xcoor,ycoor){
        let ret_bool = true;
        if(xcoor==1){
            ret_bool = false;
        }else if(this.coordinate_matrix[xcoor-2][ycoor] == true){
            ret_bool = false;
        }
        return ret_bool;
    }

    //int int
    //ret bool
    canGoSouth(xcoor,ycoor){
        let ret_bool = true;
        if(xcoor == (this.sizeOfMaze - 2)){
            ret_bool = false;
        }else if(this.coordinate_matrix[xcoor+2][ycoor] == true){
            ret_bool = false;
        }
        return ret_bool;
    }

    //int int
    //ret bool
    canGoEast(xcoor,ycoor){
        let ret_bool = true;
        if(ycoor == (this.sizeOfMaze - 2)){
            ret_bool = false;
        }else if(this.coordinate_matrix[xcoor][ycoor+2] == true){
            ret_bool = false;
        }
        return ret_bool;
    }

    //int int
    //bool
    canGoWest(xcoor,ycoor){
        let ret_bool = true;
        if(ycoor == 1){
            ret_bool = false;
        }else if(this.coordinate_matrix[xcoor][ycoor-2] == true){
            ret_bool = false;
        }
        return ret_bool;
    }

    updateMazeDOMElements(){

    }

    //int int bool bool bool bool int
    solver(x,y,fromL,fromT,fromR,fromB,k){
        let leftW = this.isWall(x,y-1);
        let topW
    }

    //int int
    //ret bool
    isWall(x,y){

    }

    //int int
    //ret bool
    endChecker(x,y){

    }

    

    

    

    

    

    

    printDirections(){

    }

};