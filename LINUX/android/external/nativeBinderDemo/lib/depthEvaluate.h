#ifndef DEPTH_EVALUATE_H
#define DEPTH_EVALUATE_H

namespace depth_evaluation
{
// the acceptable max RSME value
#define MAX_RSME_THRESHOLD 0.1
// the acceptable max average depth error value
#define MAX_DPETH_AVERAGE_ERROR_THRESHOLD 0.15
// the acceptable max number of zero depth different with reference depth
#define MAX_DIFF_ZERO_NUM_THRESHOLD 400


struct DepthPoint
{
    float x;                 //!< X coordinate [meters]
    float y;                 //!< Y coordinate [meters]
    float z;                 //!< Z coordinate [meters]
    float noise;             //!< noise value [meters]
    short int grayValue;      //!< 16-bit gray value
    signed char depthConfidence; //!< value from 0 (invalid) to 255 (full confidence)
};

class depth_evaluate
{  
public:
	//
	depth_evaluate()
	{}
    // Initial this class with the reference depth pointcloud file
    depth_evaluate(const std::string& reference_depth_file);
    /*
     * evaluate the current depth and output the result
     * @old output
     * vector[0]: Zero error rate
     * vector[1]: current non-zero depth error square value
     * vector[2]: current RSME
     * @new output
     * true: the depth result is acceptable
     * false:the depth result is unacceptable
     * @input
     * the array of reference depth
     */
    bool evaluate_current_depth(struct DepthPoint* reference_depth);
    // get current depth from file too
    // for test
    bool evaluate_current_depth(const std::string& current_depth_file);
private:
    /*
     * Evaluation paramenter
    */
    //Measured depth number
    unsigned int depth_num;
    //current non-zero depth errror square value
    float current_error_square;
    //accumulated non-zero depth error square value
    float accu_error_square;
    //Reference depthresult
    std::vector<float> reference_depth;
    //Zero depth index in reference depth
    std::vector<unsigned int> reference_zero_index;
    //
    int reference_zero_num;
    //
    std::vector<float> current_depth;

    //Release depth data from depthpoint file
    bool get_depth_from_point(const std::string& point_file,std::vector<unsigned int>& index, int& num);
    //Release depth data from depthpoint struct
    void get_depth_from_point(DepthPoint* point, unsigned int point_num,std::vector<unsigned int>& index, int& num);
    // get current depth from file too
    // for test
    bool get_depth_from_point(const std::string& point_file, unsigned int point_num,std::vector<unsigned int>& index, int& num);
    //
    bool provide_result(int& current_zero_num, std::vector<unsigned int>& current_diff_zero_index);
};

}

#endif // DEPTH_EVALUATE_H
