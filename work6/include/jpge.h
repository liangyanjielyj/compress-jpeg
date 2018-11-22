#ifndef JPEG_ENCODER_H
#define JPEG_ENCODER_H

//mv

typedef unsigned char  uint8;
typedef signed short   int16;
typedef signed int     int32;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned int   uint;  
typedef int32 sample_array_t;


enum subsampling_t { Y_ONLY = 0, H1V1 = 1, H2V1 = 2, H2V2 = 3 };

struct params
{
    inline params() : m_quality(85), m_subsampling(H2V2), m_no_chroma_discrim_flag(false), m_two_pass_flag(false) { }

    inline bool check() const
    {
      if ((m_quality < 1) || (m_quality > 100)) return false;
      if ((uint)m_subsampling > (uint)H2V2) return false;
      return true;
    }
    int m_quality;
    subsampling_t m_subsampling;
    bool m_no_chroma_discrim_flag;
    bool m_two_pass_flag;
};

bool compress_image_to_jpeg_file_in_memory(void *pBuf, int &buf_size, int width, int height, int num_channels, const uint8 *pImage_data, const params &comp_params = params());
    


//全局变量
  
  #ifndef CONFIG

  static int m_pass_num;
  void first_pass_init();//--------------mv3
  void compute_quant_table(int32 *dst, int16 *src, const params &comp_params);//mv2
  void clear();
  void compute_huffman_table(uint *codes, uint8 *code_sizes, uint8 *bits, uint8 *val);//mv5
  void load_block_8_8_grey(int x);
  void load_block_8_8(int x, int y, int c);
  void load_block_16_8(int x, int c);
  void load_block_16_8_8(int x, int c);
  void load_quantized_coefficients(int component_num);
  void code_coefficients_pass_one(int component_num);
  void deinit();

  #endif
  

//mv
 
 /* class output_stream
  {
  public:
    virtual ~output_stream() { };
    //virtual bool put_buf(const void* Pbuf, int len) = 0;
    
    
  };*/
  
  class jpeg_encoder
  {
  public:
    jpeg_encoder();
    ~jpeg_encoder();

    bool init( int width, int height, int src_channels, const params &comp_params = params());
    bool process_scanline(const void* pScanline);
        
  private:
    jpeg_encoder(const jpeg_encoder &);
    jpeg_encoder &operator =(const jpeg_encoder &);

    //output_stream *m_pStream;
    
  
    void optimize_huffman_table(int table_num, int table_len);
    void emit_byte(uint8 i);
    void emit_word(uint i);
    void emit_marker(int marker);
    void emit_jfif_app0();
    void emit_dqt();
    void emit_sof();
    void emit_dht(uint8 *bits, uint8 *val, int index, bool ac_flag);
    void emit_dhts();
    void emit_sos();
    void emit_markers();//--------------------------- 
    void adjust_quant_table(int32 *dst, int32 *src);
    bool second_pass_init();//--------------//mv4
    bool jpg_open(int p_x_res, int p_y_res, int src_channels, const params &comp_params);//mv1
    void flush_output_buffer();
    void put_bits(uint bits, uint len);
    void code_coefficients_pass_two(int component_num);
    void code_block(int component_num);
    void process_mcu_row();
    bool terminate_pass_one();
    bool terminate_pass_two();
    bool process_end_of_image();
    void load_mcu(const void* src);
    //void init();
  };

#endif // JPEG_ENCODER
