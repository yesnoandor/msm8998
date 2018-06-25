#include "../include/common.h"

#include "depthEvaluate.h"

using namespace std;

namespace depth_evaluation
{
    depth_evaluate::depth_evaluate(const std::string& reference_depth_file):
        reference_zero_num(0),
        depth_num(0),
        accu_error_square(0.0),
        current_error_square(0.0)
    {
        if(!get_depth_from_point(reference_depth_file,reference_zero_index,reference_zero_num))
			std::cout<<"Failed to load the reference depth point\r\n";
        std::cout<<"reference_zero_num:"<<reference_zero_num<<"\r\n";
    }

	bool depth_evaluate::evaluate_current_depth(struct DepthPoint * depth)
    {
        std::vector<unsigned int> current_diff_zero_index;
        int current_zero_num = 0;
        get_depth_from_point(depth,224*172,current_diff_zero_index,current_zero_num);
        current_error_square  = 0;

        return provide_result(current_zero_num,current_diff_zero_index);
    }

    bool depth_evaluate::evaluate_current_depth(const std::string& current_depth_file)
    {
        std::vector<unsigned int> current_diff_zero_index;
        int current_zero_num = 0;
        get_depth_from_point(current_depth_file,224*172,current_diff_zero_index,current_zero_num);
        current_error_square  = 0;
        return provide_result(current_zero_num,current_diff_zero_index);

    }

    bool depth_evaluate::provide_result(int& current_zero_num, std::vector<unsigned int>& current_diff_zero_index)
    {
        for(unsigned int i = 0; i< current_depth.size(); i++)
        {
            //std::cout<<"current_diff_zero_index:"<<current_depth[i]<<"\r\n";
            if(current_depth[i] != 0.0)
            {
                current_error_square += (current_depth[i] - reference_depth[i])*(current_depth[i] - reference_depth[i]);
                //std::cout<<"current_diff_zero_index:"<<current_depth[i] - reference_depth[i]<<"\r\n";
            }
        }

        //std::cout<<"current_error_square"<<current_error_square<<"\r\n";
        std::vector<float> result;
        result.reserve(3);
		result.push_back(current_diff_zero_index.size());
        float current_average_square = current_error_square / (224*172 - current_zero_num);
        depth_num ++;
        accu_error_square += current_average_square;
		result.push_back(sqrt(current_average_square));
        result.push_back(sqrt(accu_error_square/depth_num));
		std::cout<<"Evaluation result:"<<result[0]<<" "<<result[1]<<" "<<result[2]<<std::endl;

        if(result[0] < MAX_DIFF_ZERO_NUM_THRESHOLD && result[1] < MAX_DPETH_AVERAGE_ERROR_THRESHOLD && result[2] < MAX_RSME_THRESHOLD)
            return true;
        else
            return false;
    }


    bool depth_evaluate::get_depth_from_point(const std::string& point_file,std::vector<unsigned int>& index, int& num)
    {
        std::ifstream infile(point_file.c_str(), std::ifstream::binary);
        reference_depth.clear();
        reference_depth.reserve(224*172);
        reference_depth.resize(224*172);
        if (infile.is_open())
        {
            infile.seekg(0, infile.end);
            unsigned int length = infile.tellg();
            infile.seekg(0, infile.beg);
            unsigned int depthlen = sizeof(struct DepthPoint);
            //std::cout<<"Size of depth point:"<<depthlen<<std::endl;
            struct DepthPoint point;
            for (unsigned int i = 0; i < length; i += depthlen)
            {
                infile.read((char*)&point, depthlen);
                reference_depth[i/depthlen] = point.z;;
                if(point.z == 0.0)
                {

                    index.push_back(i/depthlen);
                    num++;
                }
            }
            infile.close();
            std::cout<<"reference_depth:"<<reference_depth.size()<<"\r\n";
            return true;
        }
        else
            return false;
    }

    bool depth_evaluate::get_depth_from_point(const std::string& point_file, unsigned int point_num,std::vector<unsigned int>& index, int& num)
    {
        current_depth.clear();
        current_depth.reserve(point_num);
        current_depth.resize(point_num);
        std::ifstream infile(point_file.c_str(), std::ifstream::binary);
        if (infile.is_open())
        {
            infile.seekg(0, infile.end);
            unsigned int length = infile.tellg();
            infile.seekg(0, infile.beg);
            unsigned int depthlen = sizeof(struct DepthPoint);
            //std::cout<<"Size of depth point:"<<depthlen<<std::endl;
            struct DepthPoint point;
            for (unsigned int i = 0; i < length; i += depthlen)
            {
                infile.read((char*)&point, depthlen);
                current_depth[i/depthlen] = point.z;
                if(point.z == 0.0)
                {
                    if(reference_depth[i/depthlen] != 0.0)
                        index.push_back(i/depthlen);
                    num++;
                }
            }
            infile.close();
            return true;
        }
        else
            return false;
    }

    void depth_evaluate::get_depth_from_point(DepthPoint* point, unsigned int point_num,std::vector<unsigned int>& index, int& num)
    {
        current_depth.clear();
        current_depth.reserve(point_num);
        for(unsigned int i = 0; i < point_num; i++)
        {
            current_depth.push_back(point[i].z);
            if(point[i].z == 0.0)
            {
                if(reference_depth[i] != 0.0)
                    index.push_back(i);

                num++;
            }
        }
    }

}
