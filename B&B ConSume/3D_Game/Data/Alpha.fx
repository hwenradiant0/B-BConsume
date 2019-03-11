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
string BallBoxConSume_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Cube.x";

float4x4 gWorldMatrix : World;     //‘‹?
float4x4 gViewMatrix : View;      //?,(tT| ?)
float4x4 gProjectionMatrix : Projection;//,?

float4 gWorldLightPosition[2];
float4 gWorldCameraPosition : ViewPosition;//‘‹??X tT|X X



struct VS_INPUT // pt0 ? 
{
   float4 mPosition : POSITION; //X X
   float3 mNormal   : NORMAL;   //?? ?
   float2 mUV       : TEXCOORD0;//UV?

};

struct VS_OUTPUT // pt0 ?(Resterizer\ ?
{
   float4 mPosition   : POSITION; //X X
   float3 mDiffuse    : TEXCOORD1;//??
   float3 mViewDir    : TEXCOORD2;//tT|?
   float3 mReflection : TEXCOORD3;//?
   float2 mUV         : TEXCOORD0;//UV?
   float3 mNormal   : NORMAL;
};


VS_OUTPUT BallBoxConSume_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input ) // hX t? BallBoxConSume_Pass_0_Vertex_Shader_vs_main <\ t hX x?VS_INPUT pt0X inputt?X@ VS_OUTPUTpt0t?
{
   VS_OUTPUT Output;
   
   Output.mPosition = mul(Input.mPosition,gWorldMatrix); //pt0| ‘‹?\ ¿X
   
   //lightDir : Ö¨?
   //lightDir = ‘‹?X X X - ‘‹?X ? X
   float3 lightDir = Output.mPosition.xyz - gWorldLightPosition[0].xyz;
   lightDir = normalize(lightDir); // Ö¨? ?
   
     
   //viewDir : tT|?
   //viewDir = ‘‹?X X X - ‘‹?X tT|X X
   float3 viewDir  = normalize(Output.mPosition.xyz - gWorldCameraPosition.xyz);
   Output.mViewDir = viewDir;
   
   Output.mPosition = mul(Output.mPosition,gViewMatrix); //pt0| ?,\ ¿X
   Output.mPosition = mul(Output.mPosition,gProjectionMatrix); //pt0| ,?\ ¿X
   
   //?D ‘‹?X?<\ ¿X
   float3 worldNormal = mul(Input.mNormal,(float3x3)gWorldMatrix);
   worldNormal = normalize(worldNormal); //?X ?(??T)
   
  
   //??lX0 -[X )? ‘‹??X ?X ?
   //Output.mDiffuse = saturate(dot(-lightDir , worldNormal)*0.2 + 0.5f)*0.1;
   Output.mDiffuse = dot(-lightDir, worldNormal);
   Output.mReflection = reflect(lightDir,worldNormal);//? lX0
    
   //M§–
   Output.mUV = Input.mUV;
   Output.mNormal = Input.mNormal;

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
};
texture SpecularMap_Tex
<
   string ResourceName = "..\\Texture\\fieldstone_SM.tga";
>;
sampler2D SpecularMap = sampler_state
{
   Texture = (SpecularMap_Tex);
};


struct PS_INPUT
{
   float3 mDiffuse    : TEXCOORD1;//??
   float3 mViewDir    : TEXCOORD2;//tT|?
   float3 mReflection : TEXCOORD3;//?
   float2 mUV         : TEXCOORD0;//UV?   
   float3 mNormal   : NORMAL;
};


float4 BallBoxConSume_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR //hX t? ps_main<\ PS_INPUTpt0X InputD ??\ ?t hX X@ float4t?
{   
   //saturate : 0tXX D 0<\ 1t¡X D 1\ ¿ΩX?ht?
   float4 albedo = tex2D(DiffuseMap,Input.mUV);
   float4 diffuse =float4(gLightColor,1) * albedo * float4(saturate(Input.mDiffuse),0.1f);
     
   float3 viewDir    = normalize(Input.mViewDir);//tT| ? ?
   float3 reflection = normalize(Input.mReflection);//? ?
   
   float3 specular = 0; //?
   if(diffuse.x >0)
   {

      //specular = saturate(dot(reflection,-viewDir));
      specular = pow(saturate(dot(reflection,-viewDir)),SpecularPower);
      
      //§òXÏı
      float4 specularIntensity  = tex2D(SpecularMap, Input.mUV);
      specular *= specularIntensity.rgb * gLightColor;
   }
   
   float3 ambient = float3(0.1f,0.1f,0.1f);

   float3 worldNormal = mul(Input.mNormal,(float3x3)gWorldMatrix);
   worldNormal = normalize(worldNormal); //?X ?(??T)

   float3 Dir_light = gWorldLightPosition[1].xyz;
   Dir_light = normalize(Dir_light);


   float4 direction = (0.2 +  dot(-Dir_light, worldNormal) * 0.2f) * albedo;

   float4 test = float4(diffuse + specular + ambient + direction  , 1.0f);
   test.a = 0.8;
   return test;

}



//--------------------------------------------------------------//
// Technique Section for BallBoxConSume
//--------------------------------------------------------------//
technique BallBoxConSume
{
   pass Pass_0
   {
      VertexShader = compile vs_3_0 BallBoxConSume_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_3_0 BallBoxConSume_Pass_0_Pixel_Shader_ps_main();
   }

}

