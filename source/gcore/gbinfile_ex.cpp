#include "gbinfile_ex.h"
#include "gfile.h"
#include "gbytes.h"

#define G_BINARY_DOCUMNET_BUFFER_SIZE 4096

namespace gsystem { // gsystem
namespace detail { // gsystem.detail

GBinFile_Ex::GBinFile_Ex(const GString &sFileName)
: GFile_Ex(sFileName)
{

}

GBinFile_Ex::~GBinFile_Ex()
{

}

gbyte GBinFile_Ex::Format() const
{
	return GFile::BINARY_FILE;
}

gbool GBinFile_Ex::GetByte(gbyte &b)
{
	if (EndOfFile() || !CanRead())
	{
		return false;
	}

	gint ib = fgetc(m_pFileStream);
	if (EOF == ib)
	{
		return false;
	}

	b = static_cast<gbyte>(ib);
	return true;
}

gbool GBinFile_Ex::PutByte(gbyte b)
{
	if (!Valid() || !CanWrite())
	{
		return false;
	}

	if (EOF == fputc(b, m_pFileStream))
	{
		return false;
	}
	return false;
}

gbool GBinFile_Ex::Read(gsize size, GBytes &bytes)
{
	if (EndOfFile() || !CanRead() || size <= 0)
	{
		return false;
	}
	gsize bytes_old_size = bytes.Size();
	gsize bytes_new_size = bytes_old_size + size;
	if (bytes_new_size > bytes.Capacity())
	{
		bytes.Reserve(bytes_new_size);
	}

	gsize real_bytes_new_size = fread(bytes.Tail(), sizeof(gbyte), size, m_pFileStream);
	if (real_bytes_new_size == 0)
	{
		return false;
	}
	bytes.Resize(bytes_old_size + real_bytes_new_size);
	return true;
}

gbool GBinFile_Ex::ReadAll(GBytes &bytes)
{
	if (!Valid() || !CanRead())
	{
		return false;
	}

	// 旧的文件游标备份
	glong old_tell = Tell();

	if (!Seek(0, GFile::SEEK_MODE_END))
	{
		// 还原游标
		Seek(old_tell, GFile::SEEK_MODE_START);
		return false;
	}

	glong all_size = Tell();
	if (all_size < 0)
	{
		// 还原游标
		Seek(old_tell, GFile::SEEK_MODE_START);
		return false;
	}

	// 将游标设置到初始位置
	Rewind();
	if (!Read(all_size, bytes))
	{
		// 还原游标
		Seek(old_tell, GFile::SEEK_MODE_START);
		return false;
	}

	return true;
}

gbool GBinFile_Ex::Write(const GBytes &bytes)
{
	if (!Valid() || !CanWrite())
	{
		return false;
	}
	if (0 == fwrite(bytes.Head(), sizeof(gbyte), bytes.Size(), m_pFileStream))
	{
		return false;
	}
	return true;
}

gcstring GBinFile_Ex::OpenMode() const
{
	switch(m_nOpenMode)
	{
		case GFile::NO_OPEN:
			return GNULL;
		case GFile::ONLY_READ:
			return "rb";
		case GFile::ONLY_WIRTE:
			return "wb";
		case GFile::READ_WIRTE:
			return "rb+";
		case GFile::APPEND:
			return "ab";
		default:
			break;
	}
	return GNULL;
}

} // namespace gsystem.detail
} // namespace gsystem

#undef G_BINARY_DOCUMNET_BUFFER_SIZE