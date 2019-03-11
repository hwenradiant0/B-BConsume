//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// BallBoxConSume
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string BallBoxConSume_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

float4x4 gWorldMatrix : World;              //‘‹?
float4x4 gWorldViewProjectionMatrix : WorldViewProjection;//‘‹*?,?

float4 gWorldLightPosition
<
   string UIName = "gWorldLightPosition";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 500.00, 500.00, -500.00, 1.00 ); //‘‹??X ? X
float4 gWorldCameraPosition : ViewPosition;//‘‹??X tT|X X



struct VS_INPUT // pt0 ? 
{
   float4 mPosition : POSITION; //X X
   float3 mNormal   : NORMAL;   //?? ?
   float3 mTangent  : TANGENT;  // 
   float3 mBinormal : BINORMAL; //Öï 
   float2 mUV       : TEXCOORD0;//UV?

};

struct VS_OUTPUT // pt0 ?(Resterizer\ ?
{
   float4 mPosition   : POSITION; //X X
   float3 mLightDir   : TEXCOORD1;//Ö¨X )•°0
   float3 mViewDir    : TEXCOORD2;//tT|?
   float2 mUV         : TEXCOORD0;
   float3 T           : TEXCOORD3;// 
   float3 B           : TEXCOORD4;//Öï 
   float3 N           : TEXCOORD5;//?

};


VS_OUTPUT BallBoxConSume_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input ) // hX t? BallBoxConSume_Pass_0_Vertex_Shader_vs_main <\ t hX x?VS_INPUT pt0X inputt?X@ VS_OUTPUTpt0t?
{
   VS_OUTPUT Output;
   
   Output.mPosition = mul(Input.mPosition, gWorldViewProjectionMatrix );//pt0| ‘‹*?,?\ ¿X
   
   //‘‹??X îX X
   float4 worldPosition = mul(Input.mPosition,gWorldMatrix);
   
   //lightDir : Ö¨?
   //lightDir = ‘‹?X X X - ‘‹?X ? X
   float3 lightDir = worldPosition.xyz - gWorldLightPosition.xyz;
   Output.mLightDir = normalize(lightDir);// Ö¨? ?
     
   //viewDir : tT|?
   //viewDir = ‘‹?X X X - ‘‹?X tT|X X
   float3 viewDir = normalize(worldPosition.xyz - gWorldCameraPosition.xyz);
   Output.mViewDir = viewDir;
   
   //?,  , Öï D ‘‹?\ ¿XX? ?
   float3 worldNormal = mul( Input.mNormal, (float3x3)gWorldMatrix );
   Output.N = normalize(worldNormal);
   
   float3 worldTangent = mul(Input.mTangent, (float3x3)gWorldMatrix );
   Output.T = normalize(worldTangent);
   
   float3 worldBinormal = mul(Input.mBinormal, (float3x3)gWorldMatrix );
   Output.B = normalize(worldBinormal);
      
   //Ooutput<\ M§– ? ?
   Output.mUV = Input.mUV;
   
   return Output;
   
}


float SpecularPower
<
   string UIName = "SpecularPower";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 10.00 );//?X p??
float4 ObjectColor
<
   string UIName = "ObjectColor";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 0.00, 0.00, 0.00, 1.00 );//<¥X ?
float3 gLightColor
<
   string UIName = "gLightColor";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 1.00, 1.00, 1.00 );//[X ?
texture DiffuseMap_Tex
<
   string ResourceName = "..\\..\\..\\..\\..\\..\\..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Fieldstone.tga";
>;
sampler2D DiffuseMap = sampler_state
{
   Texture = (DiffuseMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};
texture SpecularMap_Tex
<
   string ResourceName = "..\\..\\..\\..\\..\\..\\PopeShaderBookCodeSamplesKOR\\05_DiffuseSpecularMapping\\fieldstone_SM.tga";
>;
sampler2D SpecularMap = sampler_state
{
   Texture = (SpecularMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};
texture NormalMap_Tex
<
   string ResourceName = "..\\..\\..\\..\\..\\..\\..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\FieldstoneBumpDOT3.tga";
>;
sampler2D NormalMap = sampler_state
{
   Texture = (NormalMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};


struct PS_INPUT
{
   float2 mUV         : TEXCOORD0;//UV? 
   float3 mLightDir   : TEXCOORD1;//Ö¨X )•°0
   float3 mViewDir    : TEXCOORD2;//tT|?
   float3 T           : TEXCOORD3;// 
   float3 B           : TEXCOORD4;//Öï 
   float3 N           : TEXCOORD5;//?  
};


float4 BallBoxConSume_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR //hX t? ps_main<\ PS_INPUTpt0X InputD ??\ ?t hX X@ float4t?
{  
   //??M§ò\Ä0 ?D }??M§ò\Ä0 }¥¯ M@ (0~1)D -1~1\ ?
   float3 tangentNormal = tex2D(NormalMap, Input.mUV).xyz;
   tangentNormal = normalize(tangentNormal * 2 -1);
 
   //T,B,N °L\ ?D X?ÃÏ
   float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));
   // ? H?àî ?D ‘‹?<\ ¿XX?X?? TNB=?,(TBN)
   TBN = transpose(TBN);
   
   //‘‹ ??X ?D lh
   float3 worldNormal = mul(TBN,tangentNormal);
   
   //??X ?
   float3 lightDir = normalize(Input.mLightDir);
   float3 diffuse = saturate(dot(worldNormal,-lightDir));//saturate : 0tXX D 0<\ 1t¡X D 1\ ¿ΩX?ht?
   
   //?? }? ??X ?[X …¡D ?
   float4 albedo = tex2D(DiffuseMap, Input.mUV);
   diffuse = gLightColor * albedo.rgb * diffuse;
   
   float3 specular = 0; //?
   if(diffuse.x > 0)
   {
      //Ö¨X ¨°0| lX?tT|?| ??
      float3 reflection = reflect(lightDir,worldNormal);
      float3 viewDir = normalize(Input.mViewDir);
      
      //specular = saturate(dot(reflection,-viewDir));
      specular = pow(saturate(dot(reflection,-viewDir)),SpecularPower);
      
      //§òXÏıD }? [X …¡, ?X ë– ?
      float4 specularIntensity  = tex2D(SpecularMap, Input.mUV);
      specular *= specularIntensity.rgb * gLightColor;   
   }
   float3 ambient = float3(0.1f,0.1f,0.1f) * albedo;
   
   return float4(diffuse + specular + ambient + ObjectColor , 1.0f);
}



//--------------------------------------------------------------//
// Technique Section for BallBoxConSume
//--------------------------------------------------------------//
technique BallBoxConSume
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 BallBoxConSume_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 BallBoxConSume_Pass_0_Pixel_Shader_ps_main();
   }

}

