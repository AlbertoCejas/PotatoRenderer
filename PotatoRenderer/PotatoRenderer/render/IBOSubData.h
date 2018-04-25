#ifndef _INDEX_BUFFER_OBJECT_SUB_DATA_H_
#define _INDEX_BUFFER_OBJECT_SUB_DATA_H_

#include <cstdint>

class IBOSubData
{
	public:

		IBOSubData(bool isStatic, int maxIndices);
		~IBOSubData();

		inline int getNumOfIndices() const { return currentNumOfIndices; }
		inline int getMaxNumOfIndices() const { return maxNumOfIndices; }

		void setIndices(const int* indices, int count);
		void updateIndices(const int* indices, int offset, int count);

	private:

		uint32_t                            IBOhandle;
		int32_t                             currentNumOfIndices;
		int32_t                             maxNumOfIndices;
		int32_t*                            indices;
		bool                                isStatic;
		bool                                isBound;
		bool                                isDirty;

};

#endif