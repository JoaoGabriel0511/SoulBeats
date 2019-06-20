#include "../include/TileMap.h"

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated) {
    this->tileSet = tileSet;
    this->scale = 1;
    this->offsetX = 0;
    this->offsetY = 0;
    this->paralaxX = 1;
    this->paralaxY = 1;
    Load(file);
}

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet, float scale, int offsetX, int offsetY, float paralaxX, float paralaxY) : Component(associated) {
    this->tileSet = tileSet;
    this->scale = scale;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    this->paralaxX = paralaxX;
    this->paralaxY = paralaxY;
    Load(file);
}

void TileMap::Load(string file){
    int row = 0;
    ifstream myFile;
    string line;
    myFile.open(file);
    cout<<"Lendo o tileMap: "<<endl;
    while(getline(myFile,line)){
        if(row == 0){
            mapWidth = stoi(line.substr(0,3));
            mapHeight = stoi(line.substr(4,7));
            mapDepth = stoi(line.substr(8,9));
            cout<<stoi(line.substr(0,3))<<" "<<stoi(line.substr(4,7))<<" "<<stoi(line.substr(8,9))<<endl;
        }
        if(row > 1) {
            for(int i = 0; i < 4 * mapWidth; i = i + 4) {
                if(stoi(line.substr(i,i+3)) < 10) {
                    cout<<0;
                }
                if(stoi(line.substr(i,i+3)) < 100) {
                    cout<<0;
                }
                cout<< stoi(line.substr(i,i+3))<< " ";
                tileMatrix.push_back(stoi(line.substr(i,i+3))-1);
            }
            cout<<endl;
        }
        row++;
    }
}

void TileMap::SetTileSet(TileSet* tileSet){
    this->tileSet = tileSet;
}

int TileMap::At(int x, int y, int z){
    int aux;
    int aux2;
    int pos;
    int index;
    aux = mapHeight * mapWidth * z;
    aux2 = mapWidth * y;
    pos = x + aux + aux2;
    index = tileMatrix[pos] + 1;
    return index;
}

void TileMap::Render() {
    for(int i = 0; i < mapDepth; i++) {
        RenderLayer(i,Camera::pos.x,Camera::pos.y);
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
    int aux = mapHeight * mapWidth * layer;
    int aux2 = 0;
    int aux3 = 0;
    float posx = 0;
    float posy = 0;
    for (int i = aux; i < aux + mapHeight * mapWidth; i++) {
        aux2 = i - aux;
        if( aux2 >= mapWidth * (aux3+ 1)) {
            aux3++;
            posy = posy + tileSet->GetHeight() * scale;
        }
        aux2 = aux2 - mapWidth * aux3;
        posx = aux2 * tileSet->GetWidth() * scale;
        if(Camera::IsOnCamera({posx + offsetX, posy + offsetY, tileSet->GetWidth() * scale, tileSet->GetHeight() * scale}, paralaxX, paralaxY)){
            if(tileSet->RenderTile(tileMatrix[i], posx + cameraX * paralaxX, posy + cameraY * paralaxY, scale, offsetX, offsetY)){
                //cout<<"carregou tile pos("<<posx<<","<<posy<<") index: "<<tileMatrix[i]<<endl;
            } else {
                //cout<<"falha ao carregar tile pos("<<posx<<","<<posy<<") index: "<<tileMatrix[i]<<endl;
            }
        }
    }
}

int TileMap::GetWidth(){
    return mapWidth;
}

int TileMap::GetHeight(){
    return mapHeight;
}

int TileMap::GetDepth(){
    return mapDepth;
}

float TileMap::GetScale() {
    return scale;
}

bool TileMap::Is(string type) {
    if(type == "TileMap") {
        return true;
    } else {
        return false;
    }
}

TileSet* TileMap::GetTileSet() {
    return tileSet;
}

void TileMap::Update(float dt) {
}

TileMap::~TileMap(){
}