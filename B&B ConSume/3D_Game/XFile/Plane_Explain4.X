xof 0303txt 0032
template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}


Frame Box001 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh  {
  18;
  -200.000000;0.000000;-150.000000;,
  200.000000;0.000000;-150.000000;,
  -200.000000;0.000000;150.000000;,
  200.000000;0.000000;150.000000;,
  -200.000000;1.000000;-150.000000;,
  200.000000;1.000000;-150.000000;,
  -200.000000;1.000000;150.000000;,
  200.000000;1.000000;150.000000;,
  200.000000;1.000000;-150.000000;,
  -200.000000;1.000000;-150.000000;,
  200.000000;0.000000;-150.000000;,
  200.000000;1.000000;-150.000000;,
  200.000000;0.000000;150.000000;,
  -200.000000;1.000000;150.000000;,
  200.000000;1.000000;150.000000;,
  -200.000000;0.000000;150.000000;,
  -200.000000;1.000000;-150.000000;,
  -200.000000;0.000000;-150.000000;;
  10;
  3;4,7,5;,
  3;7,4,6;,
  3;0,8,1;,
  3;8,0,9;,
  3;10,7,3;,
  3;7,10,11;,
  3;12,13,2;,
  3;13,12,14;,
  3;15,16,17;,
  3;16,15,6;;

  MeshNormals  {
   5;
   0.000000;1.000000;0.000000;,
   0.000000;0.000000;-1.000000;,
   1.000000;0.000000;0.000000;,
   0.000000;0.000000;1.000000;,
   -1.000000;0.000000;0.000000;;
   10;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;;
  }

  MeshMaterialList  {
   1;
   10;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material PDX07_-_Default {
    1.000000;1.000000;1.000000;1.000000;;
    3.200000;
    0.000000;0.000000;0.000000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "Explain_4.jpg";
    }
   }
  }

  MeshTextureCoords  {
   18;
   0.000000;1.000000;,
   1.000000;1.000000;,
   1.000000;1.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;0.000000;,
   1.000000;1.000000;;
  }
 }
}

Frame Object001 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh  {
  4;
  -200.000000;0.000000;-150.000000;,
  200.000000;0.000000;-150.000000;,
  -200.000000;0.000000;150.000000;,
  200.000000;0.000000;150.000000;;
  2;
  3;0,3,2;,
  3;3,0,1;;

  MeshNormals  {
   1;
   0.000000;-1.000000;0.000000;;
   2;
   3;0,0,0;,
   3;0,0,0;;
  }

  MeshMaterialList  {
   1;
   2;
   0,
   0;

   Material PDX08_-_Default {
    1.000000;1.000000;1.000000;1.000000;;
    3.200000;
    0.000000;0.000000;0.000000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "Explain_Back.jpg";
    }
   }
  }

  MeshTextureCoords  {
   4;
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;;
  }
 }
}